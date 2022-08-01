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
		CreateExtLogger(lname);
		ExtLoggerWarn(lname, "Logging test");
		return 0;
	}
	extern "C" TESTEXTENSION_API int HeliumStart(list<any> argument) {
		ExtLoggerCrit(lname, "HeliumStart()!");
		return 0;
	}
	extern "C" TESTEXTENSION_API int HeliumStop(list<any> argument) {
		ExtLoggerCrit(lname, "HeliumStop()!");
		return 0;
	}
	extern "C" TESTEXTENSION_API int ExtensionUnload(list<any> argument) {
		ExtLoggerCrit(lname, "ExtensionUnload()!");
		ExtLoggerInfo(lname, "Destructing the extension logger.");
		DeleteExtLogger(lname);
		return 0;
	}
	extern "C" TESTEXTENSION_API int ServerStart(list<any> argument) {
		ExtLoggerCrit(lname, "ServerStart()!");
		return 0;
	}
	extern "C" TESTEXTENSION_API int ServerInitializationFinish(list<any> argument) {
		try {
			list<any>::iterator it;
			it = argument.begin();
			cout << any_cast<string>(*it) << endl;
			it++;
			cout << any_cast<tm>(*it).tm_hour << ":" 
			 	<< any_cast<tm>(*it).tm_min << ":" 
				<< any_cast<tm>(*it).tm_sec << endl;
			it++;
			cout << any_cast<string>(*it) << endl;
			it++;
			cout << any_cast<string>(*it) << endl;
			it++;
			cout << any_cast<double>(*it) << endl;
			it++;
		}
		catch (...) {
			;
		}
		return 0;
	}
	extern "C" TESTEXTENSION_API int ServerStop(list<any> argument) {
		ExtLoggerCrit(lname, "ServerStop()!");
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
	extern "C" TESTEXTENSION_API int ServerOutput(list<any> argument) {
		string server_name = any_cast<string>(argument.back())
			, server_output = any_cast<string>(argument.front())
			, logger_output;
		logger_output.append(server_name)
			.append(" ")
			.append(server_output);
		return 0;
	}
	extern "C" TESTEXTENSION_API int PlayerInput(list<any> argument) {
		return 0;
	}
}
