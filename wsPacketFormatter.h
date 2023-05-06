#ifndef WS_PACKET_FORMATTER_H
#define WS_PACKET_FORMATTER_H

#include <cstring>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "geom.h"

#define TXT_MSG '1'
#define GPS_MSG '2'

#define MAX_WS_PACKET_SIZE	220 // TODO: better bufferSize
#define MAX_AUTHOR_LEN          25
#define MAX_CONTENT_LEN         140

coordinates getWsPacketCoords(const char * str);

const char * getWsPacketAuthor(const char * str);

const char * getWsPacketContent(const char * str);

const char * getNewWsPacket(coordinates dest, const char * author, const char * message);

int checkWsPacketFormat(const char * str);


#endif
