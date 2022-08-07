#include"HeliumLogger.h"
#include"pch.h"

namespace HeliumAPI {
	typedef int (*debugprintptr)(string);
	typedef int (*createptr)(string);
	typedef int (*deleteptr)(string);
	typedef int (*loggingptr)(string, string);

	HELIUMAPI_API int HeliumExtensionDebugPrint(string debugprint) {
		auto rawptr = HeliumAPIMap.at("HeliumExtensionDebugPrint");
		debugprintptr ptr = (debugprintptr)rawptr;
		return ptr(debugprint);
	}
	HELIUMAPI_API int CreateExtensionLogger(string name) {
		auto ptr = (createptr)HeliumAPIMap.at("CreateExtLogger");
		return ptr(name);
	}
	HELIUMAPI_API int DeleteExtensionLogger(string name) {
		auto ptr = (deleteptr)HeliumAPIMap.at("DeleteExtLogger");
		return ptr(name);
	}
	HELIUMAPI_API int ExtensionLogDebug(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerDebug");
		return ptr(loggername, raw);
	}
	HELIUMAPI_API int ExtensionLogInfo(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerInfo");
		return ptr(loggername, raw);
	}
	HELIUMAPI_API int ExtensionLogWarn(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerWarn");
		return ptr(loggername, raw);
	}
	HELIUMAPI_API int ExtensionLogCrit(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerCrit");
		return ptr(loggername, raw);
	}
	HELIUMAPI_API int ExtensionLogError(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerError");
		return ptr(loggername, raw);
	}
	HELIUMAPI_API int ExtensionLog(string loggername, string raw, int level) {
		switch (level)
		{
		case 0:
			return ExtensionLogDebug(loggername, raw);
		case 1:
			return ExtensionLogInfo(loggername, raw);
		case 2:
			return ExtensionLogWarn(loggername, raw);
		case 3:
			return ExtensionLogError(loggername, raw);
		case 4:
			return ExtensionLogCrit(loggername, raw);
		default:
			return ExtensionLogInfo(loggername, raw);
		}
	}
}