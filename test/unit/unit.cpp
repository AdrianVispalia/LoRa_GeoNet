#include "unit.h"


void printTestResult(std::string groupName, std::string testName, int result) {
	if (result != 0)
		return;

	std::cout << COLOR_RED << "[!] " << groupName << ": test ";
	std::cout << testName << " failed" COLOR_RESET << std::endl;
}


void printTestGroupResult(std::string groupName, int total, int successes) {
	std::string color = COLOR_GREEN;
	if (total != successes) {
		if (successes / total > 0.5) color = COLOR_YELLOW;
		else color = COLOR_RED;
	}
	std::cout << color << "[-] " << groupName << " tests: [" << successes;
	std::cout << "/" << total << "]" << COLOR_RESET << std::endl << std::endl;
}


int testGroup(std::string groupName, test * tests, size_t testsLength) {
	int successes = 0;
	int testResult;

	for (size_t i = 0; i < testsLength; i++) {
		successes += testResult = tests[i].function();
		printTestResult(groupName, tests[i].name, testResult);
	}

	printTestGroupResult(groupName, testsLength, successes);

	return successes == testsLength;
}
