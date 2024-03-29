#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <QueueList.h>
//#include <QueueArray.h>
//#include <ArduinoQueue.h>


#define DEBUG_TELEGRAM 0

#if DEBUG_TELEGRAM
#include <UniversalTelegramBot.h>
#endif

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
#define NODE_NAME "LoRa Node - A"

#if DEBUG_TELEGRAM
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
#endif

#pragma once // TODO: check if needed

struct ArrayInfo {
  uint8_t* data;
  size_t size;
};
//QueueArray<uint8_t[MAX_LORA_PACKET_SIZE]> msgQueue;
//ArduinoQueue<uint8_t[MAX_LORA_PACKET_SIZE]> msgQueue(4);
//QueueList<uint8_t> msgSizeQueue;
QueueList<ArrayInfo> msgQueue;
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
    while (!LoRa.beginPacket()) {
    //  delay(10);
    };
    Serial.println("before LoRa write");
    LoRa.write(packet, packetSize);
    //LoRa.print(packet);
    Serial.println("after LoRa write");
    int packetTransmitted = LoRa.endPacket();
    //displayString("LoRa sent: " + String((char*)packet) + " result: " + String(packetTransmitted), 300);
    Serial.println("LoRa sent: " + String((char*)packet) + " result: " + String(packetTransmitted));

    #if DEBUG_TELEGRAM
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
    displayString(NODE_NAME, 1000);

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
    //Serial.printf("AP: %s\n", WiFi.softAPIP().toString().c_str());
    displayString("AP: " + String(WiFi.softAPIP()), 500);


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

    if (!(info->final) || info->index != 0 || info->len != len || info->opcode != WS_TEXT) return;
    //if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    
    data[len] = 0;
    if (!checkWsPacketFormat((char*)data)) return;

    char packet_type = (char)data[0];
    displayString("WsMsg: " + String((char*)data), 2000);
    size_t bSize = 0;
    uint8_t tmpBuffer[MAX_LORA_PACKET_SIZE];
    String wsPacket = "";
    coordinates thisp, coords;
    const char * author;
    const char * content;
    struct ArrayInfo msg;

    switch (packet_type) {
      case TXT_MSG:
        Serial.println("txt msg");
        //const char * content = getWsPacketContent(wsPacket.c_str());
        //displayString("About to transmit in lora: " + String(content), 2000);
        wsPacket = String((char*)data);
        ws.textAll(wsPacket.c_str());
        //Serial.println("after wsTextAll");
        thisp = getCoordinates(localPos);
        //Serial.println("after this coords");
        coords = getWsPacketCoords(wsPacket.c_str());
        //Serial.println("after packet coords");
        author = getWsPacketAuthor(wsPacket.c_str());
        //Serial.println("after get author");
        content = getWsPacketContent(wsPacket.c_str());
        //Serial.println("after get content");
        bSize = getNewLoraPacket(thisp, coords,
            author, content, &tmpBuffer[0]);
        Serial.println("before pushing the transmit packet");
        msg.data = (uint8_t*)malloc(sizeof(uint8_t) * MAX_LORA_PACKET_SIZE);
        msg.size = bSize;
        memcpy(msg.data, tmpBuffer, bSize);
        msgQueue.push(msg);
        //msgQueue.enqueue(tmpBuffer);
        //msgSizeQueue.push(bSize);
        //transmitPacket(&tmpBuffer[0], bSize);
        Serial.println("after pushing the transmit packet");
        break;
      case GPS_MSG:
        displayString("GPS msg it was", 2000);
        localPos = getCartesianPoint(getWsPacketCoords((char*)data));
        break;
      default:
        displayString("Unknown msg: " + String((char*)data), 2000);
        break;
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
    //Serial.println(var); // TODO: check if erasable
    // if(var == "STATE") { if (ledState) { return "ON"; } else { return "OFF"; } }
    return String();
}

void loop() {
    ws.cleanupClients();
    // displayString("Still running loop", 500); // TODO: remove later

    if (LoRa.parsePacket()) {
        packetBufferLength = 0;
        memset(packetBuffer, 0, sizeof(packetBuffer));
        while (LoRa.available()) {
            packetBuffer[packetBufferLength] = (uint8_t)LoRa.read();
            packetBufferLength++;
        }

        Serial.println("LoRa packet received, content: " + String(getLoraPacketContent(&packetBuffer[0], packetBufferLength)));

        Serial.println("checkFormat: " + String(checkLoraPacketFormat(&packetBuffer[0], packetBufferLength)));
        if (checkLoraPacketFormat(&packetBuffer[0], packetBufferLength) != 0) {
          Serial.println("LoRa packet has invalid format!!!!!!!!!!");
          return;
        }

        ws.textAll(getNewWsPacket(
                getLoraPacketDestCoords(&packetBuffer[0], packetBufferLength),
                getLoraPacketAuthor(&packetBuffer[0], packetBufferLength),
                getLoraPacketContent(&packetBuffer[0], packetBufferLength)
        ));

        displayString("Received a LoRa packet ", 300);
    }

    //if (!msgQueue.isEmpty() && !msgSizeQueue.isEmpty()) {
    if (!msgQueue.isEmpty()) {
      Serial.println("msgQueue poping 1 msg");
      //packetBuffer = msgQueue.pop();
      //msgQueue.pop(packetBuffer);
      //packetBufferLength = msgSizeQueue.pop();
      //Serial.println("Obtained msg: " + String(getLoraPacketContent(&packetBuffer[0], packetBufferLength)));
      struct ArrayInfo msg = msgQueue.pop();
      Serial.println("Obtained msg: " + String(getLoraPacketContent(msg.data, msg.size)));

     Serial.println("before REAL transmit packet");
     transmitPacket(msg.data, msg.size);
     Serial.println("after REAL transmit packet");
      
    }
}
