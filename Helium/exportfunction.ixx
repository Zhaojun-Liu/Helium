module;

#include<map>
#include<string>

export module Helium.ExportFunction;

using namespace std;

export{
	extern map<string, void*> HeliumExportFunctionMap;
	int InitFuncMap();
}