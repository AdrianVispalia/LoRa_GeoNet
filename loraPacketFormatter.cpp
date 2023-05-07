#include "loraPacketFormatter.h"

coordinates getLoraPacketSrcCoords(uint8_t * packet, size_t packetSize) {
    coordinates coords = {
        .lat = ((coord_dt*)packet)[0],
        .lon = ((coord_dt*)packet)[1],
    };
    return coords;
}

coordinates getLoraPacketDestCoords(uint8_t * packet, size_t packetSize) {
    coordinates coords ={
        .lat = ((coord_dt*)packet)[2],
        .lon = ((coord_dt*)packet)[3],
    };
    return coords;
}

const char * getLoraPacketAuthor(uint8_t * packet, size_t packetSize) {
    packet = packet + (sizeof(coord_byte_dt) * 4) / sizeof(uint8_t);
    packetSize -= (sizeof(coord_byte_dt) * 4) / sizeof(uint8_t);
    int split;
    for (split = 0; split < packetSize; split++)
        if (packet[split] == (uint8_t)'|') break;

    char* buffer = (char*)malloc(split + 1);
    if (buffer == NULL) return NULL;

    buffer[split] = '\0';
    strncpy((char*)buffer, (char*)packet, split);
    return (const char *)buffer;
}

const char * getLoraPacketContent(uint8_t * packet, size_t packetSize) {
    packet = packet + (sizeof(coord_byte_dt) * 4) / sizeof(uint8_t);
    packetSize -= (sizeof(coord_byte_dt) * 4) / sizeof(uint8_t);
    int split;
    for (split = 0; split < packetSize - 1; split++)
        if (packet[split] == (uint8_t)'|') break;

    packet = packet + (split + 1) * sizeof(uint8_t);
    char* buffer = (char*)malloc(packetSize - split);
    if (buffer == NULL) return NULL;

    strncpy((char*)buffer, (char*)packet, packetSize - split - 1);
    buffer[strnlen((char*)packet, packetSize - split - 1)] = '\0';
    return (const char *)buffer;
}

size_t getNewLoraPacket(coordinates src, coordinates dest, const char * author,
                const char * content, uint8_t* buffer) {
    coord_dt elements[4] = { src.lat, src.lon, dest.lat, dest.lon };
    for (int i = 0; i < 4; i++)
        ((coord_byte_dt*)buffer)[i] = ((coord_byte_dt*)elements)[i];

    size_t bufferLength = sizeof(coord_byte_dt) * 4 / sizeof(uint8_t);
    size_t authorLength = strnlen(author, MAX_AUTHOR_LEN);
    size_t contentLength = strnlen(content, MAX_CONTENT_LEN);

    strncpy((char*)(buffer + bufferLength), author, authorLength);
    buffer[bufferLength + authorLength] = (uint8_t)'|';

    strncpy((char*)(buffer + bufferLength + authorLength + 1), content, contentLength);
    return sizeof(coord_byte_dt) * 4 / sizeof(uint8_t) + authorLength + 1 + contentLength;
}

int checkLoraPacketFormat(uint8_t * packet, size_t packetSize) {
    if (packetSize < 7)
        return 0;

    int counter = 0;
    for (int i = sizeof(coord_byte_dt) * 4 / sizeof(uint8_t); i < packetSize; i++)
        if (packet[i] == '|') counter++;

    if (counter == 1)
        return 0;

    return -(counter + 1);
}
