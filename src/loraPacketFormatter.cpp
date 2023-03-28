#include "loraPacketFormatter.h"

coordinates getLoraPacketSrcCoords(uint8_t *packet) {
    coordinates coords = {
        .lat = (float)(uint16_t)*(packet),
        .lon = (float)(uint16_t)*(packet + 1)
    };
    return coords;
}

coordinates getLoraPacketDestCoords(uint8_t *packet) {
    coordinates coords = {
        .lat = (float)(uint16_t)*(packet + 2),
        .lon = (float)(uint16_t)*(packet + 3)
    };
    return coords;
}

std::string getLoraPacketAuthor(uint8_t *packet) {
    std::string tmp = ((char *)(packet + 8));
    return tmp.substr(0, tmp.find('|'));
}

std::string getLoraPacketContent(uint8_t *packet) {
    std::string tmp = ((char *)(packet + 8));
    return tmp.substr(tmp.find('|') + 1);
}

std::string getNewLoraPacket(coordinates src, coordinates dest, std::string author, std::string content) {
    uint8_t buffer[8];
    uint16_t elements[4] = { src.lat, src.lon, dest.lat, dest.lon };
    memcpy(buffer, elements, 8);
    return (char*)buffer + author + "|" + content;
}

int checkLoraPacketFormat(uint8_t *packet, int size) {
    if (size < 7)
        return 0;

    int counter = 0;
    for (int i = 0; i < size; i++) {
        if (packet[i] == '|') counter++;
    }
    if (counter != 1)
        return 0;
    
    return 1;
}