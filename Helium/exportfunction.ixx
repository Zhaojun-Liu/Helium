/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Helium-DevTeam/Helium
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

module;

#define EXP_FUNCPTR_TYPE(ret, name, ...) ret (*fp##name)(__VA_ARGS__)
#define ADD_EXP_FUNC(namestr, name) HeliumExportFunctionMap.insert(pair<string, void*>(namestr, (void*)name))

#include<map>
#include<string>
#include<boost/dll.hpp>
#include<boost/dll/import.hpp>

export module Helium.ExportFunction;

import <string>;
import Helium.CommandCallback;
import Helium.CommandQueue;
import Helium.Commands;
import Helium.Config;
import Helium.ErrorExit;
import Helium.Events;
import Helium.Exception;
import Helium.Extension;
import Helium.InitDirectory;
import Helium.Internationalization;
import Helium.Logger;
import Helium.MinecraftServer;
import Helium.Parser;
import Helium.Utils;
import Helium.UUIDManager;
import Helium.XMLUtils;
import Helium.Version;

using namespace std;
using namespace boost::dll;

export {
	namespace Helium {
		shared_library heliumapilib;
		const fs::path apipath("./extensions/HeliumAPI.dll");
		map<string, void*> HeliumExportFunctionMap;

		int InitFuncMap();
		int LoadHeliumAPI();
		int TransferFuncMap();
		int UnloadHeliumAPI();

		int InitFuncMap() {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "Building Helium API map..." << hendl;
			ADD_EXP_FUNC("HeliumExtensionDebugPrint", HeliumExtensionDebugPrint);
			ADD_EXP_FUNC("CreateExtLogger", CreateExtLogger);
			ADD_EXP_FUNC("DeleteExtLogger", DeleteExtLogger);
			ADD_EXP_FUNC("ExtLoggerDebug", ExtLoggerDebug);
			ADD_EXP_FUNC("ExtLoggerInfo", ExtLoggerInfo);
			ADD_EXP_FUNC("ExtLoggerWarn", ExtLoggerWarn);
			ADD_EXP_FUNC("ExtLoggerError", ExtLoggerError);
			ADD_EXP_FUNC("ExtLoggerCrit", ExtLoggerCrit);

			ADD_EXP_FUNC("GetHeliumVersion", GetHeliumVersion);

			ADD_EXP_FUNC("EventIDToDesc", EventIDToDesc);
			ADD_EXP_FUNC("EventIDToName", EventIDToName);
			ADD_EXP_FUNC("TraceEvent", TraceEvent);
			ADD_EXP_FUNC("UntraceEvent", UntraceEvent);
			ADD_EXP_FUNC("IsEventTraced", IsEventTraced);
			ADD_EXP_FUNC("BlockEvent", BlockEvent);
			ADD_EXP_FUNC("UnblockEvent", UnblockEvent);
			ADD_EXP_FUNC("IsEventBlocked", IsEventBlocked);
			ADD_EXP_FUNC("SetEventDesc", SetEventDesc);
			ADD_EXP_FUNC("SetEventName", SetEventName);
			ADD_EXP_FUNC("DispatchEvent", DispatchEvent);
			ADD_EXP_FUNC("RegisterEventListner", RegisterEventListner);

			log << HLL::LL_INFO << "Helium API map was successfully built" << hendl;
			return 0;
		}

		int LoadHeliumAPI() {
			log << HLL::LL_INFO << "Start Loading HeliumAPI.dll" << hendl;
			heliumapilib.load(apipath);
			if (heliumapilib.has("TransferFuncMap")) {
				log << HLL::LL_INFO << "Successfully Loaded HeliumAPI!" << hendl;
				auto& transfer = heliumapilib.get<int(map<string, void*> funcmap)>("TransferFuncMap");
				transfer(HeliumExportFunctionMap);
			}
			else {
				HeliumErrorExit(true, "Can't find TransferFuncMap() in the HeliumAPI.dll", ", try to use another HeliumAPI.dll");
			}
			return 0;
		}

		int TransferFuncMap() {
			return 0;
		}

		int UnloadHeliumAPI() {
			return 0;
		}
	}
}