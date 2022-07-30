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
	HELIUMAPI_API int CreateExtLogger(string name) {
		auto ptr = (createptr)HeliumAPIMap.at("CreateExtLogger");
		return ptr(name);
	}
	HELIUMAPI_API int DeleteExtLogger(string name) {
		auto ptr = (deleteptr)HeliumAPIMap.at("DeleteExtLogger");
		return ptr(name);
	}
	HELIUMAPI_API int ExtLoggerDebug(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerDebug");
		return ptr(loggername, raw);
	}
	HELIUMAPI_API int ExtLoggerInfo(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerInfo");
		return ptr(loggername, raw);
	}
	HELIUMAPI_API int ExtLoggerWarn(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerWarn");
		return ptr(loggername, raw);
	}
	HELIUMAPI_API int ExtLoggerCrit(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerCrit");
		return ptr(loggername, raw);
	}
	HELIUMAPI_API int ExtLoggerError(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerError");
		return ptr(loggername, raw);
	}
}