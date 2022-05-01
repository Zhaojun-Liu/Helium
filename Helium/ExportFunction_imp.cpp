/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
* ----------------------------------------------------------------------------------------
* Helium Copyright (C) 2021-2022 HeliumDevTeam
*
* This file is a part of Helium
*
* Helium is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

#define EXP_FUNCPTR_TYPE(ret, name, ...) ret (*fp##name)(__VA_ARGS__);
#define ADD_EXP_FUNC(namestr, name) HeliumExportFunctionMap.insert(pair<string, void*>(namestr, name));

module;

#include<map>

module Helium.ExportFunction;

import <string>;
import Helium.Extension;
import Helium.Logger;

using namespace std;

namespace Helium {
	EXP_FUNCPTR_TYPE(void, HeliumExtensionDebugPrint, string)

	map<string, void*> HeliumExportFunctionMap;

	int InitFuncMap() {
		HeliumEndline hendl;
		log << "Building Helium API map..." << hendl;
		HeliumExportFunctionMap.insert(pair<string, void*>("HeliumExtensionDebugPrint", (void*)HeliumExtensionDebugPrint));
		log << "Helium API map successfully built" << hendl;
		return 0;
	}

	int LoadHeliumAPI() {
		return 0;
	}

	int TransferFuncMap() {
		return 0;
	}

	int UnloadHeliumAPI() {
		return 0;
	}
}