#pragma once

#include "pch.h"
#include <common/hooks/WinHookEvent.h>
#include <FancyZonesLib/WindowUtils.h>
#include <common/logger/logger.h>
#include <common/utils/winapi_error.h>

class FZWindow
{
public:
    FZWindow()
    {
        if (!hHook)
        {
            HMODULE dll = LoadLibrary(L".\\FancyZonesHookDll.dll");
            if (!dll)
            {
                auto lastError = GetLastError();
                Logger::error(L"Failed LoadLibrary: {} / {}", lastError, get_last_error_or_default(lastError));
            }

            HOOKPROC addr = reinterpret_cast<HOOKPROC>(GetProcAddress(dll, "HookProc"));
            if (!addr)
            {
                auto lastError = GetLastError();
                Logger::error(L"Failed GetProcAddress: {} / {}", lastError, get_last_error_or_default(lastError));
            }

            hHook = SetWindowsHookEx(WH_CALLWNDPROC, addr, dll, 0);
            if (!hHook)
            {
                auto lastError = GetLastError();
                Logger::error(L"Failed SetWindowsHookEx: {} / {}", lastError, get_last_error_or_default(lastError));
            }
        }
    }

    ~FZWindow()
    {
        if (hHook)
        {
            UnhookWindowsHookEx(hHook);
            hHook = NULL;
        }
    };

private:
    inline static HHOOK hHook = nullptr;
};
