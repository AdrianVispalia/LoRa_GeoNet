#include "loraPacketFormatterTests.h"


int testSrcLoraPacket() {
	coordinates src = { .lat = 0.5, .lon = 1.7 };
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	std::string author = "adrian";
	std::string content = "this is a message!";

	std::string packet = getNewLoraPacket(src, dest, author, content);
	return src == getLoraPacketSrcCoords((uint8_t*)packet.c_str());
}

int testDestLoraPacket() {
	coordinates src = { .lat = 0.5, .lon = 1.7 };
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	std::string author = "adrian";
	std::string content = "this is a message!";

	std::string packet = getNewLoraPacket(src, dest, author, content);
	return dest == getLoraPacketDestCoords((uint8_t*)packet.c_str());
}

int testAuthorLoraPacket() {
	coordinates src = { .lat = 0.5, .lon = 1.7 };
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	std::string author = "adrian";
	std::string content = "this is a message!";

	std::string packet = getNewLoraPacket(src, dest, author, content);
	return author == getLoraPacketAuthor((uint8_t*)packet.c_str());
}

int testContentLoraPacket() {
	coordinates src = { .lat = 0.5, .lon = 1.7 };
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	std::string author = "adrian";
	std::string content = "this is a message!";

	std::string packet = getNewLoraPacket(src, dest, author, content);
	return content == getLoraPacketContent((uint8_t*)packet.c_str());
}


int testLoraPacketFormatter() {
	test tests[] = {
		{ .function = testSrcLoraPacket, .name = "testSrc" },
		{ .function = testDestLoraPacket, .name = "testDest" },
		{ .function = testAuthorLoraPacket, .name = "testAuthor" },
		{ .function = testContentLoraPacket, .name = "testContent" }
	};
	int testsLength = sizeof(tests) / sizeof(tests[0]);

	return testGroup("LoraPacketFormatter", tests, testsLength);
}
