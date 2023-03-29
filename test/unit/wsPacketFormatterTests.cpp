#include "wsPacketFormatterTests.h"

int testCoordsWsPacket() {
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	std::string author = "adrian";
	std::string content = "this is a message!";

	std::string packet = getNewWsPacket(dest, author, content);
	return dest == getWsPacketCoords(packet);
}

int testAuthorWsPacket() {
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	std::string author = "adrian";
	std::string content = "this is a message!";

	std::string packet = getNewWsPacket(dest, author, content);
	return author == getWsPacketAuthor(packet);
}

int testContentWsPacket() {
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	std::string author = "adrian";
	std::string content = "this is a message!";

	std::string packet = getNewWsPacket(dest, author, content);
	return content == getWsPacketContent(packet);
}


int testWsPacketFormatter() {
	test tests[] = {
		{ .function = testCoordsWsPacket, .name = "testCoords" },
		{ .function = testAuthorWsPacket, .name = "testAuthor" },
		{ .function = testContentWsPacket, .name = "testContent" }
	};
	int testsLength = sizeof(tests) / sizeof(tests[0]);

	return testGroup("WsPacketFormatter", tests, testsLength);
}
