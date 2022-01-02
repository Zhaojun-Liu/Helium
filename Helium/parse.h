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

#ifndef _H_PARSE
#define _H_PARSE

#define NULL 0
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include<regex>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<thread>

#include"events.h"
#include"utils.h"
namespace Helium {

	using namespace std;

	class ParseEvent {
	public:
		ParseEvent();

		int SetParseRegex(regex* preg);
		int AddResultStringRegex(regex* preg);
		int AddResultStringRegex(vector<regex> pregvec);

	protected:
		regex parseregex;
		vector<regex> resultstringsregex;
		vector<int> eventnum;
		bool parseenable;
	};

	typedef struct ServerStart {
		LONG port = NULL;
		ServerStart() {
			this->port = 0;
		}
	} ServerStartEvent;

	typedef struct ServerStarted {
		long itime;
		ServerStarted() {
			this->itime = 0;
		}
	}ServerStarted;

	class Info {
	private:
		bool IsPlayer = false;
		char* lpRawOutput = NULL;
		char* lpPlayer = NULL;
		char* lpContent = NULL;
	public:
		Info() {/*do something*/ }
		bool isPlayer() {
			return IsPlayer;
		}
		bool isServer() {
			return !IsPlayer;
		}
	};

	//[10:36:31] [Server thread/INFO]: Time elapsed: 15215 ms

	class VanillaParser {
	public:
		WINAPI VanillaParser();
		WINAPI ~VanillaParser();
		void* WINAPI parse(const char*);
	private:
		ServerStarted _stdcall parseServerStarted(const char*);
		ServerStart _stdcall parseServerStart(const char*);
		Info WINAPI parsePlayerInfo(const char*);
	};

}

#endif // !_H_PARSE
