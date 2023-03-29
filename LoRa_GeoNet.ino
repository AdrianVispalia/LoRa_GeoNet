#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <UniversalTelegramBot.h>
#include "secrets.h"
#include "geom.h"
#include "wsPacketFormatter.h"
#include "loraPacketFormatter.h"
#include "pageHtml.h"
#include "iconXml.h"

#include <Arduino.h>
#include <Wire.h> 
#include "SSD1306Wire.h" 
#define OLED_SCREEN   SSD1306Wire
#define OLED_ADDR     0x3C
#define OLED_SDA      21
#define OLED_SCL      22
#define OLED_RST      -1

#define LORA_MOSI     27
#define LORA_MISO     19
#define LORA_CLK      5
#define LORA_NSS      18
#define LORA_RST      23
#define LORA_DIO0     26
#define LORA_BAND     868E6

#define PROXIMITY_DISTANCE 1000
#define DEBUG_TELEGRAM 0

#if DEBUG_TELEGRAM
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
#endif


uint8_t packetBuffer[MAX_LORA_PACKET_SIZE];
size_t packetBufferLength = 0;
OLED_SCREEN display(OLED_ADDR, OLED_SDA, OLED_SCL);
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
point localPos = { .x = 0, .y = 0, .z = 0 };
barrier barrs[0] = {};


void displayString(String text, int delayTime) {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(display.getWidth() / 2, display.getHeight() / 2, text);
    display.display();
    Serial.println("displayString: " + text);
    delay(delayTime);
}

int transmitPacket(uint8_t* packet, int packetSize) {
    while (LoRa.beginPacket()) { delay(10); };
    LoRa.write(packet, packetSize);
    //LoRa.print(packet);
    int packetTransmitted = LoRa.endPacket();
    //displayString("LoRa sent: " + packet + " result: " + String(packetTransmitted), 300);
    #if DEBUG_TELEGRAM
    //coordinates coords = get_coordinates(localPos);
    bot.sendMessage(CHAT_ID, author + String(" just sent: ") + String(packet) + 
      String(" from ") + String(coords.lat) + String(",") + String(coords.lon), "");
    #endif
    return packetTransmitted;
}

void setup() {
    Serial.begin(115200);
    while (!Serial);
    

    if (OLED_RST > 0) {
        pinMode(OLED_RST, OUTPUT);
        for (int i = 0; i < 3; i++) {
            digitalWrite(OLED_RST, i % 2 == 0 ? HIGH : LOW);
            delay(100);
        }
    }

    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_16);
    displayString("LoRa Node - A", 1000);

    #if DEBUG_TELEGRAM
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        displayString("Wifi Connect Fail", 1000);
        esp_restart();
    }
    client.setInsecure();

    Serial.print("Connected to: " + WiFi.SSID());
    displayString("IP: " + WiFi.localIP().toString(), 1000);    
    #endif

    SPI.begin(LORA_CLK, LORA_MISO, LORA_MOSI, LORA_NSS);
    LoRa.setPins(LORA_NSS, LORA_RST, LORA_DIO0);
    if (!LoRa.begin(LORA_BAND)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    displayString("LoRaNode Ready", 1000);
    

    WiFi.softAP(AP_SSID, AP_PASSWORD);
    Serial.printf("AP: %s\n", WiFi.softAPIP().toString().c_str());
    displayString(String(WiFi.softAPIP()), 500);

    initWebSocket();
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", index_html, wsProcessor);
    });
    server.on("/Telegram_Logo.svg", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "image/svg+xml", icon_xml, wsProcessor);
    });
    
    server.begin();
}

void handleWsMsg(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        data[len] = 0;
        if (!checkWsPacketFormat((char*)data)) return;

        int type = data[0];
        if (type != (int)GPS_MSG && type != (int)TXT_MSG) {
                displayString("Unknown msg: " + String((char*)data), 2000);
        }
        if (type == (int)TXT_MSG) {
              String wsPacket = (char*)data;
              ws.textAll(wsPacket.c_str());
              String packet = getNewLoraPacket(getCoordinates(localPos), getWsPacketDestCoords(wsPacket.c_str()),
                getWsPacketAuthor(wsPacket.c_str()), getWsPacketContent(wsPacket.c_str())).c_str();
              transmitPacket(packet);
        }
        if (type == (int)GPS_MSG) {
                localPos = getCartesianPoint(getWsPacketDestCoords((char*)data));
        }
    }
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
        case WS_EVT_DATA:
            handleWsMsg(arg, data, len);
            break;
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
            break;
    }
}

void initWebSocket() {
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
}

String wsProcessor(const String& var){
    //Serial.println(var);
    // if(var == "STATE") { if (ledState) { return "ON"; } else { return "OFF"; } }
    return String();
}

void loop() {
    ws.cleanupClients();
    displayString("Still running loop", 500); // TODO: remove later

    if (LoRa.parsePacket()) {
        packetBufferLength = 0;
        memset(packetBuffer, 0, sizeof(packetBuffer));
        while (LoRa.available()) {
            packetBuffer[packetBufferLength] = (uint8_t)LoRa.read();
            packetBufferLength++;
        }

        if (!checkLoraPacketFormat((&packetBuffer, packetBufferLength))
          return;

        coordinates src = getLoraPacketSrcCoords(&packetBuffer, packetBufferLength);
        coordinates dest = getLoraPacketDestCoords(&packetBuffer, packetBufferLength);
        if (getSphericalDistance(getCartesianPoint(src), getCartesianPoint(dest)) <= PROXIMITY_DISTANCE) {
            ws.textAll(getNewWsPacket(
                dest,
                getLoraPacketAuthor(&packetBuffer, packetBufferLength),
                getLoraPacketContent(&packetBuffer, packetBufferLength)
            ).c_str());
        }
        
        if (retransmitDecision(src, dest, barrs, 0,  localPos)) {
            transmitPacket(packetBuffer, packetBufferLength);
            displayString("Retransmitting packet: " + String(recv), 300);
        }
        
        displayString("Received: " + recv, 300);
    }
}
