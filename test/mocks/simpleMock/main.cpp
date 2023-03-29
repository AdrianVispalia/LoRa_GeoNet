#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>
#include "node.cpp"


#define MAX_PACKET_DISTANCE	10000


bool loop(std::vector<Node>& nodes) {
	bool anyTraffic = false;
	for (Node &n : nodes) {
		if (!n.hasInbound())
			continue;

		anyTraffic = true;
		n.processPacket();
		if (!n.hasOutbound())
			continue;

		packetContainer output = n.getOutbound();
		point srcPos = n.getPos();
		std::cout << "Medium: Sending msg to other close nodes" << std::endl;
		for (int i = 0; i < nodes.size(); i++) {
			if (nodes.at(i).getNodeName() == n.getNodeName())
				continue;

			point destPos = nodes.at(i).getPos();
			if (getSphericalDistance(srcPos, destPos) < MAX_PACKET_DISTANCE)
				nodes.at(i).addInboundPacket(output);
		}
	}
	return anyTraffic;
}


int main() {
	// Preparing the initial nodes
	std::vector<Node> nodes = {};

	Node n1("Node1", 0, { 71.3, 64.6 });
	nodes.push_back(n1);

	Node n2("Node2", 1, { 70.4, 57.2 });
	nodes.push_back(n2);

	Node n3("Node3", 2, { 68.4, 65.2 });
	nodes.push_back(n3);

	// Adding the initial packets
	packetContainer p;
	p.packetSize = getNewLoraPacket(getCoordinates(n1.getPos()), getCoordinates(n3.getPos()),
			"Adrian", "Msg content!", &p.buffer[0]);
	nodes.at(0).addInboundPacket(p);

	// Loop that will end when all of the packets are extinguished
	bool traffic = true;
	do {
		traffic = loop(nodes);
	} while (traffic);
	return 0;
}
