#pragma once

#ifdef _WIN32
#include <windows.h>
#include <oleacc.h>
#endif


#include <stdio.h>

void Hook();

void Unhook();
