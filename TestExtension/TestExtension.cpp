// TestExtension.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "TestExtension.h"

using namespace std;
using namespace HeliumAPI;

namespace TestExtension {
	string lname = "TestExtension";
	extern "C" TESTEXTENSION_API int ExtensionLoad(list<any> argument) {
		cout << "Hello World from TestExtension!" << endl;
		HeliumExtensionDebugPrint("Hello World!");
		CreateExtLogger(lname);
		ExtLoggerInfo(lname, "Logging test");
		ExtLoggerWarn(lname, "Logging test");
		ExtLoggerCrit(lname, "Logging test");
		ExtLoggerError(lname, "Logging test");
		return 0;
	}
	extern "C" TESTEXTENSION_API int HeliumStartup(list<any> argument) {
		return 0;
	}
	extern "C" TESTEXTENSION_API int HeliumInitializationStart(list<any> argument) {
		return 0;
	}
	extern "C" TESTEXTENSION_API int HeliumInitializationFinish(list<any> argument) {
		return 0;
	}
	extern "C" TESTEXTENSION_API int HeliumFinalizationStart(list<any> argument) {
		return 0;
	}
	extern "C" TESTEXTENSION_API int HeliumFinalizationFinish(list<any> argument) {
		return 0;
	}
	extern "C" TESTEXTENSION_API int ExtensionUnload(list<any> argument) {
		ExtLoggerInfo(lname, "Destructing the extension logger.");
		DeleteExtLogger(lname);
		return 0;
	}
	extern "C" TESTEXTENSION_API int ServerStart(list<any> argument) {
		return 0;
	}
	extern "C" TESTEXTENSION_API int ServerInitializationFinish(list<any> argument) {
		return 0;
	}
	extern "C" TESTEXTENSION_API int ServerStop(list<any> argument) {
		return 0;
	}
	extern "C" TESTEXTENSION_API int PlayerJoin(list<any> argument) {
		return 0;
	}
	extern "C" TESTEXTENSION_API int PlayerLeave(list<any> argument) {
		return 0;
	}
	extern "C" TESTEXTENSION_API int GeneralInput(list<any> argument) {
		return 0;
	}
	extern "C" TESTEXTENSION_API int ConsoleInput(list<any> argument) {
		string input = "Get input from console : ";
		input.append(any_cast<string>(argument.front()));
		ExtLoggerInfo(lname, input);
		return 0;
	}
	extern "C" TESTEXTENSION_API int ServerInput(list<any> argument) {
		return 0;
	}
}
