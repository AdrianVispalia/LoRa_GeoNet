#ifndef LORA_PACKET_FORMATTER_H
#define LORA_PACKET_FORMATTER_H

#include <cstring>
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "geom.h"


coordinates getLoraPacketSrcCoords(uint8_t *packet);

coordinates getLoraPacketDestCoords(uint8_t *packet);

std::string getLoraPacketAuthor(uint8_t *packet);

std::string getLoraPacketContent(uint8_t *packet);

std::string getNewLoraPacket(coordinates src, coordinates dest, std::string author, std::string content);

int checkLoraPacketFormat(uint8_t *packet, int size);

#endif