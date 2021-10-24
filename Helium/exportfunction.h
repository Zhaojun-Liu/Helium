#pragma once

#ifndef _H_EXPORTFUNCTION
#define _H_EXPORTFUNCTION

#include<map>
#include<string>

namespace Helium {
	extern std::map<std::string, void*> HeliumExportFunctionMap;
	int InitFuncMap();
}

#endif // !_H_EXPORTFUNCTION
