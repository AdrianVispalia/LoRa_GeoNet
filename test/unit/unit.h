#ifndef _UNIT_H
#define _UNIT_H

#include <string>
#include <iostream>

#include "colors.h"

typedef int (* func_t)();

struct test {
        func_t function;
        const char * name;
};

void printTestResult(std::string groupName, std::string testName, int result);

void printTestGroupResult(std::string groupName, int total, int successes);

int testGroup(std::string groupName, test * tests, size_t testsLength);

#endif
