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

#include<spdlog/spdlog.h>
#include<spdlog/sinks/stdout_color_sinks.h>
#include<spdlog/sinks/daily_file_sink.h>
#include<string>
#include<sstream>

export module Helium.Logger;

#define INVALID_LOGGER NULL

using namespace std;

export{
	namespace Helium {
		enum HeliumLoggerLevel
		{
			LL_DBG,
			LL_INFO,
			LL_WARN,
			LL_ERR,
			LL_CRIT
		};
		typedef HeliumLoggerLevel HLL;

		struct HeliumEndline {};

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
			virtual ~HeliumLogger() {
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

		HeliumLogger log("Helium");
	}
}