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
module;

#define WIN32_LEAN_AND_MEAN
#define BUFSIZE 8192
#define NOT_STABLE

#include<map>
#include<thread>
#include<spdlog/spdlog.h>
#include<windows.h>
#include"tinyxml2/tinyxml2.h"

module Helium;

import <string>;

import Helium.Extension;
import Helium.MinecraftServer;

using namespace std;
using namespace tinyxml2;

namespace Helium {
    map<string, HeliumExtension> extensions;

    void HeliumInitOutput() {
        HeliumEndline hendl;
        log << HLL::LL_INFO << "  _   _      _ _" << hendl;
        log << " | | | | ___| (_)_   _ _ __ ___" << hendl;
        log << " | |_| |/ _ \\ | | | | | '_ ` _ \\" << hendl;
        log << " |  _  |  __/ | | |_| | | | | | |" << hendl;
        log << " |_| |_|\\___|_|_|\\__,_|_| |_| |_|" << hendl;
        //log << HeliumVersion.to_string() << hendl;
        log << "Copyright(C) 2021-2022 HeliumDevTeam" << hendl;
        log << "This program comes with ABSOLUTELY NO WARRANTY;" << hendl;
        log << "for details type \'#Helium show warranty\'." << hendl;
        log << "This is free software, and you are welcome to redistribute it" << hendl;
        log << "under certain conditions; type \'#Helium show conditions\' for details." << hendl;

        return;
    }
    int HeliumEnvInit() {
        SetConsoleTitleA("Helium");
#ifdef NOT_STABLE
        spdlog::set_level(spdlog::level::debug);
#else
        spdlog::set_level(spdlog::level::info);
#endif
        return 0;
    }
    int HeliumInit() {
        HeliumEndline hendl;

        log << HLL::LL_INFO << "Start Helium initialization." << hendl;

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

        if (auto ret = ReadHeliumConfig(); ret != XMLError::XML_SUCCESS) {
            if (auto iret = CreateHeliumConfig(); ret != XMLError::XML_SUCCESS) {
                HeliumErrorExit(true, true, "Failed to create the helium config file.");
            }
            HeliumErrorExit(true, true, "Failed to read helium config file, the file is created automatically.");
        }

        log << HLL::LL_INFO << "Finished Helium initialization." << hendl;
        return 0;
    }
    int HeliumStartServer() {
        HeliumEndline hendl;
        auto ret = AutoStartAllServer();
        ResumeAllServer();
        return ret;
    }
    int HeliumFin() {
        HeliumEndline hendl;

        FinShell();
        StopAllServer();

        return 0;
    }
    int HeliumMain(int argc, char* argv[]) {
        HeliumEndline hendl;
        int ret;

        HeliumEnvInit();

        InitShellEnv();
        InitBuiltinCommandTree();

        HeliumInitOutput();

        try {
            ret = HeliumInit();
        }
        catch (...) {
            log << HLL::LL_CRIT << "Helium initialization failed with a exception." << hendl;
            log << HLL::LL_CRIT << "THIS IS A CRASH, report it to us by : helium_devteam@outlook.com" << hendl;
            ret = -1;
        }

        if (ret == 0) {
            HeliumStartServer();
        }
        else {
            log << HLL::LL_WARN << "Helium initialization failed, skip starting server." << hendl;
        }

        InitShell("Helium>");
        HeliumFin();

        return ret;
    }
}