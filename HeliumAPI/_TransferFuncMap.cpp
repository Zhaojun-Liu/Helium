#include"_TransferFuncMap.h"
#include"pch.h"

namespace HeliumAPI {
	map<string, void*> HeliumAPIMap;

	typedef int (*createptr)(string);
	typedef int (*deleteptr)(string);
	typedef int (*loggingptr)(string, string);

	HELIUMAPI_API int TransferFuncMap(map<string, void*> funcmap) {
		HeliumAPIMap = funcmap;
		auto crt_ptr = (createptr)HeliumAPIMap.at("CreateExtLogger");
		crt_ptr("HeliumAPI");
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerInfo");
		string temp_str("Helium API ");
		temp_str.append(to_string(apiver)).append(" Copyright(C) 2021-2022 HeliumDevTeam");
		ptr("HeliumAPI", temp_str);
		return 0;
	}
}