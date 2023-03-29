#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <thread>
#include <chrono>

#include "./colors.h"
#include "../../../loraPacketFormatter.h"
#include "../../../geom.h"

#define PROXIMITY_DISTANCE 1000

struct packetContainer {
	uint8_t buffer[MAX_LORA_PACKET_SIZE];
	int	packetSize;
};


class Node {
	public:
		Node(std::string name, int color, coordinates coords) {
			nodeName = name;
			if (color > 4)
				color = color % 5;
			nodeColor = color;
			outbound.packetSize = 0;
			nodePos = getCartesianPoint(coords);
		}

		void printMsg(std::string msg) {
			std::string colorList[] = {
				COLOR_MAGENTA,
				COLOR_BLUE,
				COLOR_YELLOW,
				COLOR_GREEN,
				COLOR_CYAN,
			};
			std::cout << colorList[nodeColor] << nodeName;
			std::cout << ": " << msg;
			std::cout << COLOR_RESET << std::endl;
		}

		void addInboundPacket(packetContainer packet) {
			inbound.push_back(packet);
		}

		void processPacket() {
			packetContainer packetIn = inbound.back();
			inbound.pop_back();

			coordinates src = getLoraPacketSrcCoords(packetIn.buffer, packetIn.packetSize);
			coordinates dest = getLoraPacketDestCoords(packetIn.buffer, packetIn.packetSize);
			printMsg("processing this packet with the msg: " +
						getLoraPacketContent(packetIn.buffer, packetIn.packetSize) +
						" from: " +
						getLoraPacketAuthor(packetIn.buffer, packetIn.packetSize) +
						" src: " + std::to_string(src.lat) + ", " + std::to_string(src.lon) +
						" dest: " + std::to_string(dest.lat) + ", " + std::to_string(dest.lon));
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
			if (getSphericalDistance(getCartesianPoint(src), getCartesianPoint(dest)) < PROXIMITY_DISTANCE) {
				printMsg("this packet was sent to our area!");
			}

			if (retransmitDecision(src, dest, &barrs[0], barrs.size(), nodePos)) {
				printMsg("decided to retransmit this packet");
				memcpy(outbound.buffer, packetIn.buffer, packetIn.packetSize);
				outbound.packetSize = packetIn.packetSize;
			}
		}

		packetContainer getOutbound() {
			packetContainer result = { .packetSize = outbound.packetSize };
			result.packetSize = outbound.packetSize;
			outbound.packetSize = 0;
			return result;
		}

		bool hasOutbound() {
			return outbound.packetSize > 0;
		}

		bool hasInbound() {
			return inbound.size() > 0;
		}

		point getPos() {
			return nodePos;
		}

		std::string getNodeName() {
			return nodeName;
		}

	private:
		std::string nodeName;
		int nodeColor;
		point nodePos;
		std::vector<packetContainer> inbound;
		packetContainer outbound;
		std::vector<barrier> barrs;
};
