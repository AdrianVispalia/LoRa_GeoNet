#include "wsPacketFormatter.h"

coordinates getWsPacketCoords(std::string str) {
    std::string roi = "";
    for (int i = 2; i < str.size() && str[i] != '|'; i++)
        roi += str[i];
    int split = roi.find(',');
    double lat = std::stof(roi.substr(0, split));
    double lon = std::stof(roi.substr(split + 1));
    coordinates position = { .lat = lat, .lon = lon };
    return position;
}

std::string getWsPacketAuthor(std::string str) {
    std::string tmp = str.substr(2);
    tmp = tmp.substr(tmp.find('|') + 1);
    return tmp.substr(0, tmp.find('|'));
}

std::string getWsPacketContent(std::string str) {
    std::string tmp = str.substr(2);
    tmp = tmp.substr(tmp.find('|') + 1);
    return tmp.substr(tmp.find('|') + 1);
}

std::string getNewWsPacket(coordinates dest, std::string author, std::string message) {
    std::string lat_str = std::to_string(dest.lat);
    std::string lon_str = std::to_string(dest.lon);
    std::string dest_str = lat_str.substr(0, lat_str.find(".") + 3) + "," +
        lon_str.substr(0, lon_str.find(".") + 3);
    return "1|" + dest_str + "|" + author + "|" + message;
}

int checkWsPacketFormat(std::string str) {
    if (str.length() < 4)
        return false;

    int count = 0;
    for (int i = 0; i < str.size(); i++)
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
