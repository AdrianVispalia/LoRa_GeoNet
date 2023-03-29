#ifndef LORA_PACKET_FORMATTER_H
#define LORA_PACKET_FORMATTER_H

#include <cstring>
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "geom.h"

#define MAX_LORA_PACKET_SIZE	180


coordinates getLoraPacketSrcCoords(uint8_t* packet, size_t packetSize);

coordinates getLoraPacketDestCoords(uint8_t* packet, size_t packetSize);

std::string getLoraPacketAuthor(uint8_t* packet, size_t packetSize);

std::string getLoraPacketContent(uint8_t* packet, size_t packetSize);

size_t getNewLoraPacket(coordinates src, coordinates dest, std::string author,
                std::string content, uint8_t* bufferResult);

int checkLoraPacketFormat(uint8_t* packet, size_t packetSize);

#endif
