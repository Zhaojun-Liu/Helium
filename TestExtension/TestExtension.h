#ifdef TESTEXTENSION_EXPORTS
#define TESTEXTENSION_API __declspec(dllexport)
#else
#define TESTEXTENSION_API __declspec(dllimport)
#endif

#include "pch.h"

namespace TestExtension {
	extern "C" TESTEXTENSION_API int ExtensionLoad();
}