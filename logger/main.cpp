#include <iostream>

#include <AtlBase.h>
#include <AtlCom.h>
#include <UIAutomation.h>
#include <windows.h>

#include "process/process.h"
#include "keyboard/keyboard.h"

int main()
{

    MSG msg;

    hookKeyboard();
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    unhookKeyboard();

    return 0;
}