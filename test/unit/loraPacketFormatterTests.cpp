#include "loraPacketFormatterTests.h"


int testSrcLoraPacket() {
	coordinates src = { .lat = 0.5, .lon = 1.7 };
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	const char * author = "adrian";
	const char * content = "this is a message!";

	uint8_t packetBuffer[MAX_LORA_PACKET_SIZE];
	size_t packetLength = getNewLoraPacket(src, dest, author, content, packetBuffer);
	coordinates tmp = getLoraPacketSrcCoords(packetBuffer, packetLength);
	return src == getLoraPacketSrcCoords(packetBuffer, packetLength);
}

int testDestLoraPacket() {
	coordinates src = { .lat = 0.5, .lon = 1.7 };
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	const char * author = "adrian";
	const char * content = "this is a message!";

	uint8_t packetBuffer[MAX_LORA_PACKET_SIZE];
	size_t packetLength = getNewLoraPacket(src, dest, author, content, packetBuffer);
	coordinates tmp = getLoraPacketSrcCoords(packetBuffer, packetLength);
	return dest == getLoraPacketDestCoords(packetBuffer, packetLength);
}

int testAuthorLoraPacket() {
	coordinates src = { .lat = 0.5, .lon = 1.7 };
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	const char * author = "adrian";
	const char * content = "this is a message!";

	uint8_t packetBuffer[MAX_LORA_PACKET_SIZE];
	size_t packetLength = getNewLoraPacket(src, dest, author, content, packetBuffer);

	return strcmp(author, getLoraPacketAuthor(packetBuffer, packetLength)) == 0;
}

int testContentLoraPacket() {
	coordinates src = { .lat = 0.5, .lon = 1.7 };
	coordinates dest = { .lat = 0.7, .lon = 2.3 };
	const char * author = "adrian";
	const char * content = "this is a message!";

	uint8_t packetBuffer[MAX_LORA_PACKET_SIZE];
	size_t packetLength = getNewLoraPacket(src, dest, author, content, packetBuffer);
	return strcmp(content, getLoraPacketContent(packetBuffer, packetLength)) == 0;
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
