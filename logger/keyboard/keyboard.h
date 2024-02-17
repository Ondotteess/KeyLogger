#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <sstream>
#include <vector>
#include <fstream>
#include <chrono>

#include "../process/process.h"

using system_clock = std::chrono::system_clock;

void hookKeyboard();

void unhookKeyboard();
