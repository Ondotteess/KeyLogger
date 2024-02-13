#pragma once

#ifdef _WIN32
#include <windows.h>
#include <oleacc.h>
#endif


#include <stdio.h>
#include <regex>


void hookUrl();

void unhookUrl();
