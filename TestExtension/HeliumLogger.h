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
	HELIUMAPI_API int CreateExtLogger(string name);
	HELIUMAPI_API int DeleteExtLogger(string name);
	HELIUMAPI_API int ExtLoggerDebug(string loggername, string raw);
	HELIUMAPI_API int ExtLoggerInfo(string loggername, string raw);
	HELIUMAPI_API int ExtLoggerWarn(string loggername, string raw);
	HELIUMAPI_API int ExtLoggerCrit(string loggername, string raw);
	HELIUMAPI_API int ExtLoggerFatal(string loggername, string raw);
}