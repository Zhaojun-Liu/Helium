#include"HeliumLogger.h"
#include"pch.h"

namespace HeliumAPI {
	typedef int (*debugprintptr)(string);

	HELIUMAPI_API int HeliumExtensionDebugPrint(string debugprint) {
		cout << "Enter HeliumExtensionDebugPrint()!" << endl;
		auto rawptr = HeliumAPIMap.at("HeliumExtensionDebugPrint");
		debugprintptr ptr = (debugprintptr)rawptr;
		return ptr(debugprint);
	}
}