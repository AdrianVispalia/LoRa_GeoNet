#include "wsPacketFormatter.h"

coordinates getWsPacketDestCoords(std::string str) {
    std::string roi = "";
    for (int i = 2; i < str.size() && str[i] != '|'; i++)
        roi += str[i];
    int split = roi.find(',');
    float lat = std::stof(roi.substr(0, split));
    float lon = std::stof(roi.substr(split + 1));
    coordinates position = { .lat = lat, .lon = lon };
    return position;
}

std::string getWsPacketAuthor(std::string str) {
    std::string tmp = str.substr(2);
    tmp = tmp.substr(0, tmp.find('|'));
    return tmp.substr(1, tmp.find('|'));
}

std::string getWsPacketContent(std::string str) {
    std::string tmp = str.substr(2);
    tmp = tmp.substr(0, tmp.find('|'));
    return tmp.substr(tmp.find('|') + 1);
}

std::string getNewWsPacket(coordinates dest, std::string author, std::string message) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << dest.lat << "," << dest.lon; // TO CHECK
    std::string dest_str = stream.str();
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
