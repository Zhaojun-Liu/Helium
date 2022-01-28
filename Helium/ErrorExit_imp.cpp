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

#include<string>
#include<iostream>
#include<cstdarg>
#include<spdlog/spdlog.h>

module Helium.ErrorExit;

using namespace std;

namespace Helium {
	void HeliumErrorExit(bool ispause, bool uselogger, string str, ...) {
		va_list arglist;

		if (uselogger) {
			HeliumLogger logger("HeliumErrorExit");
			HeliumEndline hendl;
			va_start(arglist, str);
			logger << HLL::LL_CRIT << arglist << hendl;
			va_end(arglist);
		}
		else {
			va_start(arglist, str);
			cout << arglist << endl;
			va_end(arglist);
		}

		spdlog::drop_all();
		_flushall();
		if (ispause) system("pause");
		exit(EXIT_FAILURE);
	}
	void HeliumError_exit(bool ispause, bool uselogger, string str, ...) {
		va_list arglist;

		if (uselogger) {
			HeliumLogger logger("HeliumErrorExit");
			HeliumEndline hendl;
			va_start(arglist, str);
			logger << HLL::LL_CRIT << arglist << hendl;
			va_end(arglist);
		}
		else {
			va_start(arglist, str);
			cout << arglist << endl;
			va_end(arglist);
		}

		spdlog::drop_all();
		if (ispause) system("pause");
		_exit(EXIT_FAILURE);
	}
}