#include "loraPacketFormatter.h"

coordinates getLoraPacketSrcCoords(uint8_t* packet, size_t packetSize) {
    coordinates coords = {
        .lat = ((double*)packet)[0],
        .lon = ((double*)packet)[1],
    };
    return coords;
}

coordinates getLoraPacketDestCoords(uint8_t* packet, size_t packetSize) {
    coordinates coords ={
        .lat = ((double*)packet)[2],
        .lon = ((double*)packet)[3],
    };
    return coords;
}

std::string getLoraPacketAuthor(uint8_t* packet, size_t packetSize) {
    packet = packet + (sizeof(uint64_t) * 4) / sizeof(uint8_t);
    packetSize -= (sizeof(uint64_t) * 4) / sizeof(uint8_t);
    int split;
    for (split = 0; split < packetSize; split++)
        if (packet[split] == (uint8_t)'|') break;

    packet[split] = '\0';
    return (char*)packet;
}

std::string getLoraPacketContent(uint8_t* packet, size_t packetSize) {
    packet = packet + (sizeof(uint64_t) * 4) / sizeof(uint8_t);
    packetSize -= (sizeof(uint64_t) * 4) / sizeof(uint8_t);
    int split;
    for (split = 0; split < packetSize - 1; split++)
        if (packet[split] == (uint8_t)'|') break;

    packet = packet + (split + 1) * sizeof(uint8_t);
    return (char*)packet;
}

size_t getNewLoraPacket(coordinates src, coordinates dest, std::string author,
                std::string content, uint8_t* bufferResult) {
    double elements[4] = { src.lat, src.lon, dest.lat, dest.lon };
    for (int i = 0; i < 4; i++)
        ((uint64_t*)bufferResult)[i] = ((uint64_t*)elements)[i];

    std::string segment = author + "|" + content;
    strncpy((char*)(bufferResult + sizeof(uint64_t) * 4 / sizeof(uint8_t)),
                segment.c_str(), segment.length());
    return sizeof(uint64_t) * 4 / sizeof(uint8_t) + segment.length();
}

int checkLoraPacketFormat(uint8_t* packet, size_t packetSize) {
    if (packetSize < 7)
        return 0;

    int counter = 0;
    for (int i = 0; i < packetSize; i++)
        if (packet[i] == '|') counter++;

    if (counter != 1)
        return 0;

    return 1;
}
