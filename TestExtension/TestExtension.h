#ifdef TESTEXTENSION_EXPORTS
#define TESTEXTENSION_API __declspec(dllexport)
#else
#define TESTEXTENSION_API __declspec(dllimport)
#endif

#include "pch.h"

namespace TestExtension {
	extern "C" TESTEXTENSION_API int HeliumStartup(list<any> argument);
	extern "C" TESTEXTENSION_API int HeliumStop(list<any> argument);
	extern "C" TESTEXTENSION_API int ExtensionLoad(list<any> argument);
	extern "C" TESTEXTENSION_API int ExtensionUnload(list<any> argument);
	extern "C" TESTEXTENSION_API int ServerStart(list<any> argument);
	extern "C" TESTEXTENSION_API int ServerInitializationFinish(list<any> argument);
	extern "C" TESTEXTENSION_API int ServerStop(list<any> argument);
	extern "C" TESTEXTENSION_API int PlayerJoin(list<any> argument);
	extern "C" TESTEXTENSION_API int PlayerLeave(list<any> argument);
	extern "C" TESTEXTENSION_API int GeneralInput(list<any> argument);
	extern "C" TESTEXTENSION_API int ConsoleInput(list<any> argument);
	extern "C" TESTEXTENSION_API int ExtensionLoad(list<any> argument);
	extern "C" TESTEXTENSION_API int ServerOutput(list<any> argument);
	extern "C" TESTEXTENSION_API int PlayerInput(list<any> argument);
}