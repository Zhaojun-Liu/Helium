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

#define BUFSIZE 8192

#include<spdlog/spdlog.h>
#include"tinyxml2/tinyxml2.h"


export module Helium;

export import Helium.CommandCallback;
export import Helium.CommandQueue;
export import Helium.Commands;
export import Helium.Config;
export import Helium.ErrorExit;
export import Helium.Events;
export import Helium.Exception;
export import Helium.Extension;
export import Helium.InitDirectory;
export import Helium.Internationalization;
export import Helium.Logger;
export import Helium.MinecraftServer;
export import Helium.Parser;
export import Helium.Utils;
export import Helium.UUIDManager;
export import Helium.XMLUtils;
export import Helium.Version;

import Helium.ExportFunction;

import <string>;
import <any>;
import <list>;
import <thread>;
import <strstream>;
import <map>;
import <thread>;

using namespace std;
using namespace tinyxml2;

export{
	namespace Helium {
		int ProcessServerOutput(HeliumMinecraftServer*, string, HANDLE, HANDLE);
		int HeliumMain(int argc, char* argv[]);
		void HeliumInitOutput();
		int HeliumInit();
		int HeliumEnvInit();
		int HeliumFin();
		int HeliumStartServer();

        void HeliumInitOutput() {
            HeliumEndline hendl;
            log << HLL::LL_INFO << " _   _      _ _" << hendl;
            log << "| | | | ___| (_)_   _ _ __ ___" << hendl;
            log << "| |_| |/ _ \\ | | | | | '_ ` _ \\" << hendl;
            log << "|  _  |  __/ | | |_| | | | | | |" << hendl;
            log << "|_| |_|\\___|_|_|\\__,_|_| |_| |_|" << hendl;
            log << "Helium " << GetHeliumVersion().to_string() << hendl;
            log << "Copyright(C) 2021-2022 HeliumDevTeam" << hendl;
            log << "This program comes with ABSOLUTELY NO WARRANTY;" << hendl;
            log << "for details type \'#Helium show warranty\'." << hendl;
            log << "This is free software, and you are welcome to redistribute it" << hendl;
            log << "under certain conditions; type \'#Helium show conditions\' for details." << hendl;

            return;
        }
        int HeliumEnvInit() {
            HeliumEndline hendl;

#ifdef NOT_STABLE
            log << HLL::LL_INFO << "This is a unstable version of helium, log level set to debug." << hendl;
            spdlog::set_level(spdlog::level::debug);
#else
            spdlog::set_level(spdlog::level::info);
#endif
            return 0;
        }
        int HeliumInit() {
            log << HLL::LL_INFO << "Start Helium initialization." << hendl;

            InitShellEnv();
            InitBuiltinCommandTree();

            InitFuncMap();
            LoadHeliumAPI();
            TransferFuncMap();

            helium_event_manager.RegisterEventListener(HeliumEventList::PLAYER_INPUT, PlayerInput);

            log << HLL::LL_DBG << "Start adding dirs" << hendl;
            AddHeliumDirectory("./extensions", "The \"extension\" folder doesn't exists, creating...", HDIP::HDIP_CREATE_WARING);
            AddHeliumDirectory("./extensions/extconfigs", "The \"extensions/extconfigs\" folder doesn't exists, creating...", HDIP::HDIP_CREATE_WARING);
            AddHeliumDirectory("./logs", "The \"logs\" folder doesn't exists, creating...", HDIP::HDIP_CREATE_WARING);
            AddHeliumDirectory("./scripts", "The \"scripts\" folder doesn't exists, creating...", HDIP::HDIP_CREATE_WARING);
            AddHeliumDirectory("./scripts/initscripts", "The \"scripts/initscripts\" folder doesn't exists, creating...", HDIP::HDIP_CREATE_WARING);
            log << HLL::LL_DBG << "End adding dirs" << hendl;

            if (auto ret = InitHeliumDirectory(); ret != 0) {
                HeliumErrorExit(true, true, "Failed to initialize directory,exiting...");
            }

            auto sucext = FindAllExtensionConfig();
            log << HLL::LL_INFO << "Finded " << sucext << " extension config file" << hendl;
            sucext = LoadAllExtension();
            log << HLL::LL_INFO << "Successfully loaded " << sucext << " extensions." << hendl;
            
            if (auto ret = ReadHeliumConfig(); ret != XMLError::XML_SUCCESS) {
                if (auto iret = CreateHeliumConfig(); ret != XMLError::XML_SUCCESS) {
                    HeliumErrorExit(true, true, "Failed to create the helium config file.");
                }
                HeliumErrorExit(true, true, "Failed to read helium config file, the file is created automatically.");
            }

            InitServerEnv();

            list<any> param;
            any temp_any;
            temp_any = GetHeliumVersion();
            param.push_back(temp_any);
            helium_event_manager.DispatchEvent(HeliumEventList::HELIUM_START, param);

            log << HLL::LL_INFO << "Finished Helium initialization stage." << hendl;
            return 0;
        }
        int HeliumStartServer() {
            auto ret = AutoStartAllServer();
            ResumeAllServer();
            return ret;
        }
        int HeliumFin() {
            list<any> param;
            any temp_any;
            temp_any = GetHeliumVersion();
            param.push_back(temp_any);
            helium_event_manager.DispatchEvent(HeliumEventList::HELIUM_STOP, param);

            UnloadAllExtension();
            FinShell();
            StopAllServer();

            return 0;
        }
        int HeliumMain(int argc, char* argv[]) {
            int ret;
            log << HLL::LL_INFO << "Current Working Directory : " << argv[0] << hendl;
            HeliumEnvInit();

            HeliumInitOutput();

            try {
                ret = HeliumInit();
            }
            catch (exception& e) {
                log << HLL::LL_CRIT << "Helium initialization failed with a exception." << hendl;
                log << HLL::LL_CRIT << "Exception description : " << e.what() << hendl;
                log << HLL::LL_CRIT << "THIS IS A CRASH, report it to us by : helium_devteam@outlook.com" << hendl;
                ret = -1;
                system("pause");
                return ret;
            }

            try {
                HeliumStartServer();
            }
            catch(exception& e) {
                log << HLL::LL_ERR << "Minecraft server startup failed with a exception." << hendl;
                log << HLL::LL_ERR << "Exception description : " << e.what() << hendl;
                log << HLL::LL_ERR << "Please check your configuration and the server files' completeness." << hendl;
            }

            InitShell("Helium>");
            HeliumFin();

            return ret;
        }
	}
}