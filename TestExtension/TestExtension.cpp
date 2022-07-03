// TestExtension.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "TestExtension.h"

using namespace std;
using namespace HeliumAPI;

namespace TestExtension {
	extern "C" TESTEXTENSION_API int ExtensionLoad() {
		HeliumExtensionDebugPrint("Hello World!");
		string lname = "TestExtension";
		CreateExtLogger(lname);
		ExtLoggerInfo(lname, "Logging test");
		ExtLoggerInfo(lname, "Logging test");
		ExtLoggerInfo(lname, "Logging test");
		ExtLoggerInfo(lname, "Logging test");
		ExtLoggerInfo(lname, "Logging test");
		DeleteExtLogger(lname);
		return 0;
	}
}
