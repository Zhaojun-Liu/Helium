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

#ifndef _H_LOGGER
#define _H_LOGGER

#include<spdlog/spdlog.h>
#include<spdlog/sinks/stdout_color_sinks.h>
#include<spdlog/sinks/daily_file_sink.h>
#include<string>
#include<iostream>
#include<sstream>
namespace Helium {

#define def int _stdcall
#define INVALID_LOGGER NULL

	using namespace std;

	enum HeliumLoggerLevel
	{
		LL_DBG,
		LL_INFO,
		LL_WARN,
		LL_ERR,
		LL_CRIT
	};
	typedef HeliumLoggerLevel HLL;
	
	struct HeliumEndline{};

	class HeliumLogger
	{
	public:
		_declspec(property(get = GetLoggerName, put = SetLoggerName)) string name;

		string GetLoggerName() {
			return this->loggername;
		}
		void SetLoggerName(string n) {
			this->loggername = n;
		}
		
		HeliumLogger(string name);
		~HeliumLogger() {
			this->log->flush();
		}

		HeliumLogger& operator<<(HeliumLoggerLevel n);
		HeliumLogger& operator<<(string s);
		HeliumLogger& operator<<(const char* c);
		HeliumLogger& operator<<(int n);
		HeliumLogger& operator<<(long n);
		HeliumLogger& operator<<(double s);
		HeliumLogger& operator<<(HeliumEndline hendl);
	protected:
		int loglevel;
		string loggername;
		stringstream buffer;
		shared_ptr<spdlog::logger> log;
		shared_ptr<spdlog::logger> filelog;
	};
}

#endif // !_H_LOGGER