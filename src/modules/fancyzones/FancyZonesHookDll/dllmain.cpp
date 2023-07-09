// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <fstream>
#include <string>

inline static HHOOK hHook = nullptr;

//extern "C" __declspec(dllexport) LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
//{
//    /*if (nCode == HC_ACTION)
//        {
//            if (wParam == WM_KEYDOWN || wParam == WM_KEYUP)
//            {
//                PKBDLLHOOKSTRUCT kbdHookStruct = reinterpret_cast<PKBDLLHOOKSTRUCT>(lParam);
//                if (((kbdHookStruct->vkCode == keys) || ...))
//                {
//                    callback(wParam == WM_KEYDOWN);
//                }
//            }
//        }*/
//
//    std::wstring text;
//    switch (nCode)
//    {
//    case HCBT_CREATEWND:
//    {
//        text += L"HCBT_CREATEWND - ";
//    }
//    break;
//    case HCBT_DESTROYWND:
//    {
//        text += L"HCBT_DESTROYWND - ";
//    }
//    break;
//    case HCBT_MINMAX:
//    {
//        text += L"HCBT_MINMAX - ";
//    }
//    break;
//    case HCBT_MOVESIZE:
//    {
//        text += L"HCBT_MOVESIZE - ";
//    }
//    break;
//    default:
//        break;
//    }
//
//    if (!text.empty())
//    {
//        HWND window = (HWND)wParam;
//
//        DWORD cTxtLen = GetWindowTextLength(window);
//        auto pszMem = static_cast<LPWSTR>(VirtualAlloc(NULL, static_cast<SIZE_T>(cTxtLen) + 1, MEM_COMMIT, PAGE_READWRITE));
//        GetWindowText(window, pszMem, cTxtLen + 1);
//
//        wchar_t className[MAX_PATH];
//        GetClassName(window, className, MAX_PATH);
//
//        text += pszMem;
//        text += L" / ";
//        text += className;
//    }
//
//    std::wfstream myfile;
//    myfile.open("D:/cbt_hook.txt", std::fstream::app);
//    myfile << text << "\n";
//    myfile.close();
//
//    return CallNextHookEx(hHook, nCode, wParam, lParam);
//}

//extern "C" __declspec(dllexport) LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
//{
//    std::wstring text;
//    switch (nCode)
//    {
//    //case HSHELL_REDRAW:
//    //{
//    //    text += L"HSHELL_REDRAW - ";
//    //}
//    //break;
//    case HSHELL_WINDOWACTIVATED:
//    {
//        text += L"HSHELL_WINDOWACTIVATED - ";
//    }
//    break;
//    //case HSHELL_WINDOWCREATED:
//    //{
//    //    text += L"HSHELL_WINDOWCREATED - ";
//    //}
//    //break;
//    //case HSHELL_WINDOWDESTROYED:
//    //{
//    //    text += L"HSHELL_WINDOWDESTROYED - ";
//    //}
//    //break;
//    //case HSHELL_WINDOWREPLACED:
//    //{
//    //    text += L"HSHELL_WINDOWREPLACED - ";
//    //}
//    //break;
//    default:
//        break;
//    }
//
//    if (!text.empty())
//    {
//        HWND window = (HWND)wParam;
//
//        DWORD cTxtLen = GetWindowTextLength(window);
//        auto pszMem = static_cast<LPWSTR>(VirtualAlloc(NULL, static_cast<SIZE_T>(cTxtLen) + 1, MEM_COMMIT, PAGE_READWRITE));
//        GetWindowText(window, pszMem, cTxtLen + 1);
//
//        wchar_t className[MAX_PATH];
//        GetClassName(window, className, MAX_PATH);
//
//        text += pszMem;
//        text += L" / ";
//        text += className;
//    
//        std::wfstream myfile;
//        myfile.open("D:/shell_hook.txt", std::fstream::app);
//        myfile << text << "\n";
//        myfile.close();
//    }
//
//    return CallNextHookEx(hHook, nCode, wParam, lParam);
//}

extern "C" __declspec(dllexport) LRESULT CALLBACK HookProc(WNDPROC prevProc, HWND window, int messageCode, WPARAM wParam, LPARAM lParam)
{
    std::wstring text;
    switch (messageCode)
    {
    case WM_STYLECHANGED:
        text += L"WM_STYLECHANGED";
        break;
    default:
        text += std::to_wstring(messageCode);
        break;
    }

    if (!text.empty())
    {
        HWND window = (HWND)wParam;

        DWORD cTxtLen = GetWindowTextLength(window);
        auto pszMem = static_cast<LPWSTR>(VirtualAlloc(NULL, static_cast<SIZE_T>(cTxtLen) + 1, MEM_COMMIT, PAGE_READWRITE));
        GetWindowText(window, pszMem, cTxtLen + 1);

        wchar_t className[MAX_PATH];
        GetClassName(window, className, MAX_PATH);

        text += pszMem;
        text += L" / ";
        text += className;

        std::wfstream myfile;
        myfile.open("D:/wm_hook.txt", std::fstream::app);
        myfile << text << "\n";
        myfile.close();
    }

    return CallNextHookEx(hHook, messageCode, wParam, lParam);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

