#include "pch.h"
#include <workspaces-common/GuidUtils.h>
#include <WorkspacesLib/utils.h>
#include <WorkspacesLib/WorkspacesData.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WorkspacesLibUnitTests
{
    TEST_CLASS(GuidUtilsTests)
    {
    public:
        TEST_METHOD(GuidFromString_Valid)
        {
            std::wstring guidStr = L"{12345678-1234-1234-1234-1234567890AB}";
            auto guidOpt = GuidFromString(guidStr);
            Assert::IsTrue(guidOpt.has_value());
            Assert::AreEqual(guidStr, GuidToString(guidOpt.value()));
        }

        TEST_METHOD(GuidFromString_Invalid)
        {
            std::wstring guidStr = L"invalid-guid";
            auto guidOpt = GuidFromString(guidStr);
            Assert::IsFalse(guidOpt.has_value());
        }
    };

    TEST_CLASS(CommandLineArgsTests)
    {
    public:
        TEST_METHOD(Split_AllTokens)
        {
            std::wstring guidStr = L"{12345678-1234-1234-1234-1234567890AB}";
            std::wstring input = guidStr + L" 1 restarted";
            auto args = split(input, L" ");
            Assert::AreEqual(guidStr, args.workspaceId);
            Assert::AreEqual(static_cast<int>(InvokePoint::Shortcut), static_cast<int>(args.invokePoint));
            Assert::IsTrue(args.isRestarted);
        }

        TEST_METHOD(Split_InvalidTokens)
        {
            std::wstring input = L"not-a-guid foo";
            auto args = split(input, L" ");
            Assert::IsTrue(args.workspaceId.empty());
            Assert::AreEqual(static_cast<int>(InvokePoint::EditorButton), static_cast<int>(args.invokePoint));
            Assert::IsFalse(args.isRestarted);
        }
    };

    TEST_CLASS(PositionTests)
    {
    public:
        TEST_METHOD(Position_ToRect)
        {
            WorkspacesData::WorkspacesProject::Application::Position pos{10, 20, 30, 40};
            auto rect = pos.toRect();
            Assert::AreEqual(10L, rect.left);
            Assert::AreEqual(20L, rect.top);
            Assert::AreEqual(40L, rect.bottom);
            Assert::AreEqual(40L, rect.right);
            Assert::AreEqual(30L, rect.right - rect.left);
            Assert::AreEqual(40L, rect.bottom - rect.top);
        }

        TEST_METHOD(Position_FromJson_InvalidType)
        {
            json::JsonObject obj;
            obj.SetNamedValue(L"X", json::value(L"bad"));
            obj.SetNamedValue(L"Y", json::value(5));
            obj.SetNamedValue(L"width", json::value(10));
            obj.SetNamedValue(L"height", json::value(15));
            auto res = WorkspacesData::WorkspacesProjectJSON::ApplicationJSON::PositionJSON::FromJson(obj);
            Assert::IsFalse(res.has_value());
        }
    };
}
