#include "geom.h"
#include "wsPacketFormatter.h"
#include "loraPacketFormatter.h"
#include "display.h"
#include "wsFunctions.h"
#include "loraFunctions.h"
#include <Arduino.h>
#include "wsFunctions.h"


#define PROXIMITY_DISTANCE 1000

uint8_t packetBuffer[MAX_LORA_PACKET_SIZE];
barrier barrs[0] = {};


void setup() {
    Serial.begin(115200);
    while (!Serial);

    setupDisplay();
    displayString("LoRa Node - A", 1000);

    setupLoRa();
    displayString("LoRaNode Ready", 1000);


    setupWebServer();
    initWebSocket();

    Serial.printf("Creating QR code..");
    printWiFiQrCode();
    Serial.printf("Setup finished");
}


void loop() {
    ws.cleanupClients();
    dnsServer.processNextRequest();

    // displayString("Still running loop", 500); // TODO: remove later
    int packetBufferLength = receiveLoRaPacket(packetBuffer);

    if (packetBufferLength > 0) {
        coordinates src = getLoraPacketSrcCoords(&packetBuffer[0], packetBufferLength);
        coordinates dest = getLoraPacketDestCoords(&packetBuffer[0], packetBufferLength);

        if (getSphericalDistance(getCartesianPoint(src), getCartesianPoint(dest)) <= PROXIMITY_DISTANCE) {
            ws.textAll(
                getNewWsPacket(
                    dest,
                    getLoraPacketAuthor(&packetBuffer[0], packetBufferLength),
                    getLoraPacketContent(&packetBuffer[0], packetBufferLength)
                )
            );
        }

        if (retransmitDecision(src, dest, barrs, 0,  localPos)) {
            transmitLoRaPacket(&packetBuffer[0], packetBufferLength); // TODO: check if change src
            displayString("Retransmitting packet ", 300);
        }

        displayString("Received a packet ", 300);
    }
}
