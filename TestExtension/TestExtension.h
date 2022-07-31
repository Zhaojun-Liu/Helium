#ifdef TESTEXTENSION_EXPORTS
#define TESTEXTENSION_API __declspec(dllexport)
#else
#define TESTEXTENSION_API __declspec(dllimport)
#endif

#include "pch.h"

namespace TestExtension {
	extern "C" TESTEXTENSION_API int HeliumStartup(list<any>);
	extern "C" TESTEXTENSION_API int HeliumInitializationStart(list<any>);
	extern "C" TESTEXTENSION_API int HeliumInitializationFinish(list<any>);
	extern "C" TESTEXTENSION_API int HeliumFinalizationStart(list<any>);
	extern "C" TESTEXTENSION_API int HeliumFinalizationFinish(list<any>);
	extern "C" TESTEXTENSION_API int ExtensionLoad(list<any>);
	extern "C" TESTEXTENSION_API int ExtensionUnload(list<any>);
	extern "C" TESTEXTENSION_API int ServerStart(list<any>);
	extern "C" TESTEXTENSION_API int ServerInitializationFinish(list<any>);
	extern "C" TESTEXTENSION_API int ServerStop(list<any>);
	extern "C" TESTEXTENSION_API int PlayerJoin(list<any>);
	extern "C" TESTEXTENSION_API int PlayerLeave(list<any>);
	extern "C" TESTEXTENSION_API int GeneralInput(list<any>);
	extern "C" TESTEXTENSION_API int ConsoleInput(list<any>);
	extern "C" TESTEXTENSION_API int ServerInput(list<any>);
	extern "C" TESTEXTENSION_API int ExtensionLoad(list<any>);
}