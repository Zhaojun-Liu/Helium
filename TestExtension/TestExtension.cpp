#include"pch.h"
#include"framework.h"
#include"TestExtension.h"

using namespace std;
using namespace HeliumAPI;

namespace TestExtension {
	string lname;
	extern "C" TESTEXTENSION_API int ExtensionLoad(list<any> argument) {
		lname = any_cast<string>(argument.front());
		CreateExtensionLogger(lname);
		ExtensionLogWarn(lname, "Logging test");
		list<any> param;
		DispatchEvent(1, param);
		param = GetExtensionMetadata("AnotherTestExtension");
		for (auto s : param) {
			ExtensionLogError(lname, any_cast<string>(s));
		}
		return 0;
	}
	extern "C" TESTEXTENSION_API int HeliumStart(list<any> argument) {
		ExtensionLogCrit(lname, "HeliumStart()!");
		return 0;
	}
	extern "C" TESTEXTENSION_API int HeliumStop(list<any> argument) {
		ExtensionLogCrit(lname, "HeliumStop()!");
		return 0;
	}
	extern "C" TESTEXTENSION_API int ExtensionUnload(list<any> argument) {
		ExtensionLogCrit(lname, "ExtensionUnload()!");
		ExtensionLogInfo(lname, "Destructing the extension logger.");
		DeleteExtensionLogger(lname);
		return 0;
	}
	extern "C" TESTEXTENSION_API int ServerStart(list<any> argument) {
		ExtensionLogCrit(lname, "ServerStart()!");
		return 0;
	}
	extern "C" TESTEXTENSION_API int ServerInitializationFinish(list<any> argument) {
		try {
			list<any>::iterator it;
			it = argument.begin();
			string server_name = any_cast<string>(*it);
			cout << any_cast<string>(*it) << endl;
			it++;
			cout << StopServer(server_name) << endl;
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
		ExtensionLogCrit(lname, "ServerStop()!");
		return 0;
	}
	extern "C" TESTEXTENSION_API int PlayerJoin(list<any> argument) {
		try {
			cout << "Player Name:" << any_cast<string>(argument.back()) << endl;
		}
		catch (...) {
			;
		}
		return 0;
	}
	extern "C" TESTEXTENSION_API int PlayerLeave(list<any> argument) {
		try {
			cout << "Player Name:" << any_cast<string>(argument.back()) << endl;
		}
		catch (...) {
			;
		}
		return 0;
	}
	extern "C" TESTEXTENSION_API int GeneralInput(list<any> argument) {
		return 0;
	}
	extern "C" TESTEXTENSION_API int ConsoleInput(list<any> argument) {
		string input = "Get input from console : ";
		input.append(any_cast<string>(argument.front()));
		ExtensionLogInfo(lname, input);
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
		try {
			auto it = argument.end();
			it--;
			it--;
			cout << any_cast<string>(*it) << endl;
			cout << any_cast<string>(argument.back()) << endl;
		}
		catch (...) {
			;
		}
		return 0;
	}
}