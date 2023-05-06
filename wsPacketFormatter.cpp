#include "wsPacketFormatter.h"

coordinates getWsPacketCoords(const char * str) {
    int split = -1;
    size_t packetLength = strnlen(str, MAX_WS_PACKET_SIZE);
    for (int i = 2; i < packetLength && str[i] != '|'; i++) {
        if (split == - 1 && str[i] == ',') {
            split = i - 2;
            break;
        }
    }
    
    if (split == -1) return {nan(""), nan("")};

    //coordinates position = {
    //    .lat = strtod(roi, NULL),
    //    .lon = strtod((roi + split + 1), NULL)
    //};
    return {
        strtod(str + 2, NULL),
        strtod((str + 2 + split + 1), NULL)
    };
}

const char * getWsPacketAuthor(const char * str) {
    size_t packetLength = strnlen(str, MAX_WS_PACKET_SIZE);

    int split = -1;
    for (int i = 2; i < packetLength; i++) {
        if (str[i] == '|') {
            split = i + 1;
            break;
        }
    }
    if (split == -1) return NULL;

    char * buffer = (char*)malloc(MAX_AUTHOR_LEN + 1);
    if (buffer == NULL) return NULL;

    memset(buffer, 0, MAX_AUTHOR_LEN + 1);
    for (int i = split; i < packetLength - split && str[i] != '|'; i++) {
        buffer[i - split] = str[i];
    }

    return (const char*)buffer;
}

const char * getWsPacketContent(const char * str) {
    size_t packetLength = strnlen(str, MAX_WS_PACKET_SIZE);
    int split = -1;
    for (int i = packetLength; i > 0; i--) {
        if (str[i] == '|') {
            split = i;
            break;
        }
    }
    if (split == -1) return NULL;

    char * buffer = (char*)malloc(packetLength - split);
    if (buffer == NULL) return NULL;

    strncpy(buffer, str + split + 1, packetLength - split - 1);
    buffer[packetLength - split - 1] = '\0';
    return (const char*)buffer;
}

const char * getNewWsPacket(coordinates dest, const char * author, const char * message) {
    char lat_str[10];
    sprintf(lat_str, "%.2f", dest.lat);
    char lon_str[10];
    sprintf(lon_str, "%.2f", dest.lon);

    size_t authorLength = strnlen(author, MAX_AUTHOR_LEN);
    size_t messageLength = strnlen(message, MAX_CONTENT_LEN);
    size_t latLength = strnlen(lat_str, 20);
    size_t lonLength = strnlen(lon_str, 20);

    char* buffer = (char*)malloc(latLength + lonLength + authorLength + messageLength + 7);
    if (buffer == NULL) return NULL;

    strncpy(buffer, "1|", 2);
    strncpy(buffer + 2, lat_str, latLength);
    buffer[latLength + 2] = ',';
    strncpy(buffer + latLength + 3, lon_str, lonLength);
    buffer[latLength + lonLength + 3] = '|';
    strncpy(buffer + latLength + lonLength + 4, author, authorLength);
    buffer[latLength + lonLength + authorLength + 4] = '|';
    strncpy(buffer + latLength + lonLength + authorLength + 5, message, messageLength);
    buffer[latLength + lonLength + authorLength + messageLength + 6] = '\0';

    return (const char*)buffer;
}

int checkWsPacketFormat(const char * str) {
    size_t packetLength = strnlen(str, MAX_WS_PACKET_SIZE);
    if (packetLength < 4)
        return false;

    int count = 0;
    for (int i = 0; i < packetLength; i++)
        if (str[i] == '|')
            count++;

    switch (str[0]) {
        case TXT_MSG:
            if (count != 3)
                return false;
            break;
        case GPS_MSG:
            if (count != 1)
                return false;
            break;
        default:
            return false;
    }

    return true;
}
