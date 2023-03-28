#include <cstring>
#include <iostream>
#include <string>

#include "unit.h"

#include "loraPacketFormatterTests.h"
#include "wsPacketFormatterTests.h"
#include "geomTests.h"


void header(std::string text) {
	std::cout << std::endl << COLOR_MAGENTA;
	std::cout << "---------------";
	std::cout << " " << text << " ";
	std::cout << "---------------";
	std::cout << COLOR_RESET << std::endl << std::endl;
}

void printTestReport(int total, int successes) {
	std::cout << std::endl << COLOR_BLUE;
	std::cout << "[i] Tests passed on ";
	std::cout << successes << " out of " << total;
	std::cout << " sections";
	std::cout << COLOR_RESET << std::endl << std::endl;
}

int main () {
	int sectionCounter = 0;
	func_t sections[] = {
		testLoraPacketFormatter,
		testWsPacketFormatter,
		testGeom
	};
	int sectionsLength = sizeof(sections) / sizeof(sections[0]);

	header("Starting Tests");

	for (int i = 0; i < sectionsLength; i++)
		sectionCounter += sections[i]();

	header("End of Tests");

	printTestReport(sectionsLength, sectionCounter);

	return 1;
}
