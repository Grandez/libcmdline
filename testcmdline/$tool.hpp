#pragma once
#include <chrono>
#include <ctime>

#include "../include/cmdline.hpp"
#include "../cmdline/include/tools.h"

using namespace std;
using namespace cmdline;
using namespace _cmdline;

class Tool {
public:
	 char** argv = nullptr;
	 int    argc = 0;
	 struct tm now;
	 Tool();
	void reset();
	int addArg(const char* arg);
	int addArg(const char* name, const char* value);
	int getArgc();
	inline char* mystrdup(const char* str);
	 
};

#ifndef __tool__
#define __tool__
extern Tool tool;
#endif
