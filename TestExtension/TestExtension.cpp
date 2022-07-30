// TestExtension.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "TestExtension.h"

using namespace std;
using namespace HeliumAPI;

namespace TestExtension {
	extern "C" TESTEXTENSION_API int ExtensionLoad(list<any>) {
		cout << "Hello World from TestExtension!" << endl;
		HeliumExtensionDebugPrint("Hello World!");
		string lname = "TestExtension";
		CreateExtLogger(lname);
		ExtLoggerInfo(lname, "Logging test");
		ExtLoggerWarn(lname, "Logging test");
		ExtLoggerCrit(lname, "Logging test");
		ExtLoggerError(lname, "Logging test");
		DeleteExtLogger(lname);
		return 0;
	}
}
