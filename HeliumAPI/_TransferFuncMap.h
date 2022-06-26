#pragma once

#include<map>
#include"pch.h"

using namespace std;

namespace HeliumAPI {
	extern map<string, void*> HeliumAPIMap;

	HELIUMAPI_API int TransferFuncMap(map<string, void*> funcmap);
}