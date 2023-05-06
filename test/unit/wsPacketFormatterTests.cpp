#include "wsPacketFormatterTests.h"

int testCoordsWsPacket() {
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	const char * author = "adrian";
	const char * content = "this is a message!";

	const char * packet = getNewWsPacket(dest, author, content);
	return dest == getWsPacketCoords(packet);
}

int testAuthorWsPacket() {
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	const char * author = "adrian";
	const char * content = "this is a message!";

	const char * packet = getNewWsPacket(dest, author, content);
	return strcmp(author, getWsPacketAuthor(packet)) == 0;
}

int testContentWsPacket() {
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	const char * author = "adrian";
	const char * content = "this is a message!";

	const char * packet = getNewWsPacket(dest, author, content);
	return strcmp(content, getWsPacketContent(packet)) == 0;
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
