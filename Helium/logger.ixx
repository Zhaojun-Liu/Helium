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

#define INVALID_LOGGER NULL

#include<spdlog/spdlog.h>
#include<spdlog/sinks/stdout_color_sinks.h>
#include<spdlog/sinks/daily_file_sink.h>
#include<string>
#include<sstream>
#include<spdlog/fmt/fmt.h>
#include<iostream>

export module Helium.Logger;

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
			~HeliumLogger() {
				this->logger->flush();
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
			shared_ptr<spdlog::logger> logger;
			string loggername;
			stringstream buffer;
			//shared_ptr<spdlog::logger> log;
		};

		HeliumEndline hendl;
		HeliumLogger log("Helium");
		auto LDBG = HLL::LL_DBG;
		auto LINFO = HLL::LL_INFO;
		auto LWARN = HLL::LL_DBG;
		auto LCRIT = HLL::LL_DBG;
		auto LFATAL = HLL::LL_DBG;
	}
}

namespace Helium {
	//shared_ptr<spdlog::sinks::daily_file_sink_mt> heliumdailysink = make_shared<spdlog::sinks::daily_file_sink_mt>("./logs/helium-log.log", 23, 59);
	//shared_ptr<spdlog::sinks::stdout_color_sink_mt> heliumconsolesink = make_shared<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::automatic);
	//static unique_ptr<spdlog::sinks::daily_file_sink_mt> heliumdailysink = make_unique<spdlog::sinks::daily_file_sink_mt>("./logs/helium-log.log", 23, 59);
	//static unique_ptr<spdlog::sinks::stdout_color_sink_mt> heliumconsolesink = make_unique<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::automatic);
	//spdlog::sinks_init_list sinklist = { heliumdailysink, heliumconsolesink };

	bool isinit = false;
	vector<spdlog::sink_ptr> sinks;

	HeliumLogger::HeliumLogger(string name) {
		this->loggername = name;
		if (!isinit) {
			sinks.push_back(make_shared<spdlog::sinks::daily_file_sink_mt>("./logs/helium-log.log", 23, 59));
			sinks.push_back(make_shared<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::automatic));
			isinit = true;
		}
		this->logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
	}

	HeliumLogger& HeliumLogger::operator<<(HeliumLoggerLevel n) {
		this->loglevel = n;
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(string s) {
		this->buffer << s;
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(const char* c) {
		this->buffer << c;
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(int n) {
		this->buffer << n;
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(long n) {
		this->buffer << n;
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(double s) {
		this->buffer << s;
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(HeliumEndline hendl) {
		string str = this->buffer.str();
		if (str.empty()) return *this;
		try {
			switch (this->loglevel) {
			case HeliumLoggerLevel::LL_DBG:
				this->logger->debug(str);
				break;
			case HeliumLoggerLevel::LL_INFO:
				this->logger->info(str);
				break;
			case HeliumLoggerLevel::LL_WARN:
				this->logger->warn(str);
				break;
			case HeliumLoggerLevel::LL_ERR:
				this->logger->error(str);
				break;
			case HeliumLoggerLevel::LL_CRIT:
				this->logger->critical(str);
				break;
			default:
				break;
			}
		}
		catch (...) {
			cout << "Logging failed" << endl;
		}
		this->buffer.str("");
		return *this;
	}
}