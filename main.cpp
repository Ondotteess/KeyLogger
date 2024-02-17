#include <iostream>

#include <AtlBase.h>
#include <AtlCom.h>
#include <UIAutomation.h>
#include <windows.h>

#include "process/process.h"
#include "keyboard/keyboard.h"
#include "url/url.h"

int main(int, char **)
{
    std::string url("");

    HWND hWnd = nullptr;
    while (1)
    {
        hWnd = FindWindowEx(nullptr, hWnd, "Chrome_WidgetWin_1", nullptr);

        // if (hWnd != nullptr)
        // {
        //     return 0;
        // }

        if (IsWindowVisible(hWnd) == 0 && GetWindowThreadProcessId(hWnd, NULL) != GetCurrentThreadId() && GetWindowTextLength(hWnd) > 0)
        {
            break;
        }
    }

    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    CComPtr<IUIAutomation> uia;
    if (SUCCEEDED(uia.CoCreateInstance(CLSID_CUIAutomation)))
    {
        CComPtr<IUIAutomationElement> root;
        if (SUCCEEDED(uia->GetRootElement(&root)))
        {
            if (find_url(uia, root, url))
            {
                std::cout << url << std::endl;
            }
            //     return 0;
        }
    }

    CoUninitialize();

    // MSG msg;

    // hookKeyboard();
    // hookUrl();
    // while (GetMessage(&msg, NULL, 0, 0))
    // {
    //     TranslateMessage(&msg);
    //     DispatchMessage(&msg);
    // }

    // unhookKeyboard();
    // unhookUrl();

    return 0;
}
