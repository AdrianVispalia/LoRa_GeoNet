#ifndef _LORA_FUNCTIONS_H
#define _LORA_FUNCTIONS_H

#include <SPI.h>
#include <LoRa.h>
#include "board_def.h"


void setupLoRa() {  
    SPI.begin(CONFIG_CLK, CONFIG_MISO, CONFIG_MOSI, CONFIG_NSS);
    LoRa.setPins(CONFIG_NSS, CONFIG_RST, CONFIG_DIO0);
    if (!LoRa.begin(LORA_PERIOD)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}


int transmitLoRaPacket(uint8_t* packet, int packetSize) {
    while (LoRa.beginPacket()) { delay(10); };
    LoRa.write(packet, packetSize);  // if it doesn't work, change for LoRa.print(packet);
    int packetTransmitted = LoRa.endPacket();
    //displayString("LoRa sent: " + packet + " result: " + String(packetTransmitted), 300);
    return packetTransmitted;
}


size_t receiveLoRaPacket(uint8_t * packetBuffer) {
    if (LoRa.parsePacket()) {
        size_t packetBufferLength = 0;
        memset(packetBuffer, 0, sizeof(packetBuffer));
        while (LoRa.available()) {
            packetBuffer[packetBufferLength] = (uint8_t)LoRa.read();
            packetBufferLength++;
        }

        if (!checkLoraPacketFormat(&packetBuffer[0], packetBufferLength))
            return (size_t)0;

        return packetBufferLength;
    }
}

#endif
