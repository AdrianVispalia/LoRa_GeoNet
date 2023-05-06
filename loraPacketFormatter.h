#ifndef LORA_PACKET_FORMATTER_H
#define LORA_PACKET_FORMATTER_H

#include <cstring>
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "geom.h"

#define MAX_LORA_PACKET_SIZE	180 // TODO: better bufferSize
#define MAX_AUTHOR_LEN          25
#define MAX_CONTENT_LEN         140


coordinates getLoraPacketSrcCoords(uint8_t * packet, size_t packetSize);

coordinates getLoraPacketDestCoords(uint8_t * packet, size_t packetSize);

const char * getLoraPacketAuthor(uint8_t * packet, size_t packetSize);

const char * getLoraPacketContent(uint8_t * packet, size_t packetSize);

size_t getNewLoraPacket(coordinates src, coordinates dest, const char * author,
                const char * content, uint8_t * bufferResult);

int checkLoraPacketFormat(uint8_t * packet, size_t packetSize);

#endif
