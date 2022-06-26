#pragma once

#include"pch.h"

using namespace std;

#ifdef HELIUMAPI_EXPORTS
#define HELIUMAPI_API extern "C" _declspec(dllexport)
#else
#define HELIUMAPI_API extern "C" _declspec(dllimport)
#endif

namespace HeliumAPI {
	HELIUMAPI_API int HeliumExtensionDebugPrint(string debugprint);
	HELIUMAPI_API class ExtensionLogger {
	protected:
		string name;
	};
}