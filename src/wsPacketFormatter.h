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


coordinates getWsPacketDestCoords(std::string str);

std::string getWsPacketAuthor(std::string str);

std::string getWsPacketContent(std::string str);

std::string getNewWsPacket(coordinates dest, std::string author, std::string message);

int checkWsPacketFormat(std::string str);


#endif
