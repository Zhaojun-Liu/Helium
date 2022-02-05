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

#include<Windows.h>
#include<thread>
#include<strstream>
#include<spdlog/spdlog.h>

#include"semver/semver.hpp"

export module Helium;

#define HELIUM_MAJORVER 0
#define HELIUM_MINORVER 6
#define HELIUM_PATCHVER 8
#define HELIUM_DEVSTAT prerelease::alpha

export import Helium.CommandQueue;
export import Helium.Commands;
export import Helium.Config;
export import Helium.ErrorExit;
export import Helium.Events;
export import Helium.ExportFunction;
export import Helium.Extension;
export import Helium.InitDirectory;
export import Helium.Logger;
export import Helium.MinecraftServer;
export import Helium.Parser;
export import Helium.Utils;
export import Helium.XMLUtils;

import <string>;

using namespace std;
using namespace semver;

export{
	namespace Helium {
		PTP_POOL heliumtp;

		int ProcessServerOutput(HeliumMinecraftServer*, string, HANDLE, HANDLE);
		int HeliumMain(int argc, char* argv[]);
		void HeliumInitOutput();
		int HeliumInit();
		int HeliumEnvInit();
		int HeliumFin();
		int HeliumStartServer();
	}
}