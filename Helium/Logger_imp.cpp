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

#include<iostream>

#include<spdlog/fmt/fmt.h>
#include<spdlog/spdlog.h>
#include<spdlog/sinks/daily_file_sink.h>
#include<spdlog/sinks/stdout_color_sinks.h>

module Helium.Logger;

import <string>;

using namespace std;

namespace Helium {
	auto heliumdailysink = make_shared<spdlog::sinks::daily_file_sink_mt>("./logs/helium-log.log", 23, 59);
	auto heliumconsolesink = make_shared<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::automatic);

	HeliumLogger::HeliumLogger(string name) {
		this->loggername = name;
		try {
			string logname = name;

			auto console_sink = make_shared<spdlog::logger>(logname, heliumconsolesink);

			logname.clear();
			logname.append(name).append("_file");
			auto file_logger = make_shared<spdlog::logger>(logname, heliumdailysink);

			spdlog::register_logger(console_sink);
			spdlog::register_logger(file_logger);
			this->log = console_sink;
			this->filelog = file_logger;
		}
		catch (const spdlog::spdlog_ex& ex) {
			cout << "Logger initalization failed(" << this->name << "), reason : " << ex.what() << endl;
		}
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
		switch (this->loglevel) {
		case HeliumLoggerLevel::LL_DBG:
			this->log->debug(this->buffer.str());
			this->filelog->debug(this->buffer.str());
			break;
		case HeliumLoggerLevel::LL_INFO:
			this->log->info(this->buffer.str());
			this->filelog->info(this->buffer.str());
			break;
		case HeliumLoggerLevel::LL_WARN:
			this->log->warn(this->buffer.str());
			this->filelog->warn(this->buffer.str());
			break;
		case HeliumLoggerLevel::LL_ERR:
			this->log->error(this->buffer.str());
			this->filelog->error(this->buffer.str());
			break;
		case HeliumLoggerLevel::LL_CRIT:
			this->log->critical(this->buffer.str());
			this->filelog->critical(this->buffer.str());
			break;
		default:
			break;
		}
		this->buffer.str("");
		return *this;
	}
}