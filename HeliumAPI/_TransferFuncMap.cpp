#include"_TransferFuncMap.h"
#include"pch.h"

namespace HeliumAPI {
	map<string, void*> HeliumAPIMap;

	HELIUMAPI_API int TransferFuncMap(map<string, void*> funcmap) {
		cout << "Enter TransferFuncMap()!" << endl;
		HeliumAPIMap = funcmap;
		return 0;
	}
}