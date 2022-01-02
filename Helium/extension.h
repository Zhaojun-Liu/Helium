/*
* Helium Pre-Alpha 0.6.1
* Copyright (C) 2021-2022 HeliumDevTeam
*
* Helium is a customizable extension system for Minecraft server which is written in C++.
* This project is inspired by the [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged).
* We target to provide a liter, faster, and more customizable choice.
* As a trade-off, we sacrifice its portability and the simplicity of writing extensions.
* (we r sry that we haven't finish the first alpha version yet, if u r interested in our project, we recommend u to use mcdr as a temporary alternative)
* This project is licensed by the GPL-3.0-or-later license.
*
* Very very special thank to contributors of the following projects:
* [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged)
* [kpeeters/tree.hh](https://github.com/kpeeters/tree.hh)
* [leethomason/tinyxml2](https://github.com/leethomason/tinyxml2/)
* [jcwangxp/Crossline](https://github.com/jcwangxp/Crossline/)
*
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
*
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*    This file is part of Helium.
*
*    Helium is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Helium is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#pragma once

#ifndef _H_EXTENSION
#define _H_EXTENSION

#include<string>
#include<vector>
#include<iostream>
#include<map>
#include<Windows.h>
#include<spdlog/spdlog.h>
#include"xmlutils.h"
#include"events.h"
#include"tinyxml2/tinyxml2.h"

using namespace std;

namespace Helium {
	class HeliumExtensionConfig {
	public:
		_declspec(property(get = GetExtConfigPath, put = PutExtConfigPath)) string Extconfigpath;
		_declspec(property(get = GetExtName, put = PutExtName)) string Extname;

		string _stdcall GetExtConfigPath() {
			return configpath;
		}
		void _stdcall PutExtConfigPath(string path) {
			this->configpath = path;
		}

		string _stdcall GetExtName() {
			return configpath;
		}
		void _stdcall PutExtName(string path) {
			this->configpath = path;
		}

		int ReadConfig();
	private:
		string configpath;
		string extname;
	};

	class HeliumExtensionFuncs {
		
	};

	class HeliumExtension {
		friend class HeliumExtensionConfig;
		friend class HeliumExtensionFuncs;

	public:
		int _stdcall LoadExt();
		int _stdcall LockExt();
		int _stdcall UnlockExt();
		int _stdcall UnloadExt();
		int _stdcall SetConfigPath(string path);

		enum ExtStat {
			EXT_STATUS_EMPTY,
			EXT_STATUS_LOADING,
			EXT_STATUS_LOADED,
			EXT_STATUS_UNLOADING,
			EXT_STATUS_LOCKED
		};
	private:
		HeliumExtensionConfig config;
		HeliumExtensionFuncs funcs;
		int extstat;
		vector<HeliumEventInstance*> EventQueue;
	};
}
#endif //!_H_EXTENSION
