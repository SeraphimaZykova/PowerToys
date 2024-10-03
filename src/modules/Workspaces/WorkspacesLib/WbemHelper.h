#pragma once

#include <comdef.h>
#include <Wbemidl.h>

class WbemHelper
{
public:
    WbemHelper() = default;
    ~WbemHelper();

    bool Initialize();

    std::wstring GetCommandLineArgs(DWORD processID) const;
    std::wstring GetExecutablePath(DWORD processID) const;

private:
    std::wstring Query(const std::wstring& query, const std::wstring& propertyName) const;

    IWbemLocator* m_locator = NULL;
    IWbemServices* m_services = NULL;
};
