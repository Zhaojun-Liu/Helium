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
	HELIUMAPI_API int CreateExtensionLogger(string name);
	HELIUMAPI_API int DeleteExtensionLogger(string name);
	HELIUMAPI_API int ExtensionLogDebug(string loggername, string raw);
	HELIUMAPI_API int ExtensionLogInfo(string loggername, string raw);
	HELIUMAPI_API int ExtensionLogWarn(string loggername, string raw);
	HELIUMAPI_API int ExtensionLogCrit(string loggername, string raw);
	HELIUMAPI_API int ExtensionLogError(string loggername, string raw);
	HELIUMAPI_API int ExtensionLog(string loggername, string raw, int level = 1);
}