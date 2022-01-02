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

#include"logger.h"
#include<spdlog/fmt/fmt.h>
namespace Helium {
	auto heliumdailysink = make_shared<spdlog::sinks::daily_file_sink_mt>("./logs/helium_log.txt", 23, 59);
	auto heliumconsolesink = make_shared<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::automatic);

	HeliumLogger::HeliumLogger(string name) {
		this->loggername = name;
		try {
			string logname = name;

			auto console_sink = make_shared<spdlog::logger>(logname, heliumconsolesink);

			logname.clear();
			logname.append(name).append("_filesink");
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