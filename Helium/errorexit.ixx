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

#include<cstdarg>
#include<spdlog/spdlog.h>
#include<boost/stacktrace.hpp>

export module Helium.ErrorExit;

import Helium.Logger;
import <string>;
import <iostream>;

using namespace std;
using namespace boost::stacktrace;

export{
	namespace Helium {
		void HeliumErrorExit(bool ispause, bool uselogger, string str, ...);
		void HeliumError_exit(bool ispause, bool uselogger, string str, ...);
		void HeliumTerminateHandler();
	}
}

namespace Helium {
	void HeliumErrorExit(bool ispause, bool uselogger, string str, ...) {
		va_list arglist;

		if (uselogger) {
			HeliumEndline hendl;
			va_start(arglist, str);
			log << HLL::LL_CRIT << arglist << hendl;
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
			HeliumEndline hendl;
			va_start(arglist, str);
			log << HLL::LL_CRIT << arglist << hendl;
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
	void HeliumTerminateHandler() {	
		try {
			log << HLL::LL_CRIT << "Helium crashed with a unexpected exception!" << hendl;
			log << HLL::LL_CRIT << "THIS IS A CRASH. Please inform us at helium_devteam@outlook.com" << hendl;
			cout << "----------------------Stacktrace----------------------" << endl;
			cout << stacktrace() << endl;
			cout << "----------------------Stacktrace----------------------" << endl;
		}
		catch (...) {
			try {
				cout << "Helium crashed with a unexpected exception!" << endl;
				cout << "THIS IS A CRASH. Please inform us at helium_devteam@outlook.com" << endl;
				cout << "----------------------Stacktrace----------------------" << endl;
				cout << stacktrace() << endl;
				cout << "----------------------Stacktrace----------------------" << endl;
			}
			catch (...) {
				cout << "Failed to get the boost::stacktrace::stacktrace()" << endl;
			}
		}
		abort();
	}
}