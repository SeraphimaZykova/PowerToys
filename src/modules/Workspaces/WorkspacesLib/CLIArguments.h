#pragma once

#include <string>

#include <WorkspacesLib/WbemHelper.h>

namespace CLIArguments
{
    inline std::wstring GetCommandLineArgs(DWORD processID, const WbemHelper& wbemHelper)
    {
        std::wstring executablePath = wbemHelper.GetExecutablePath(processID);
        std::wstring commandLineArgs = wbemHelper.GetCommandLineArgs(processID);

        if (!commandLineArgs.empty())
        {
            auto pos = commandLineArgs.find(executablePath);
            if (pos != std::wstring::npos)
            {
                commandLineArgs = commandLineArgs.substr(pos + executablePath.size());
                auto spacePos = commandLineArgs.find_first_of(' ');
                if (spacePos != std::wstring::npos)
                {
                    commandLineArgs = commandLineArgs.substr(spacePos + 1);
                }
            }
        }

        return commandLineArgs;
    }
}