/*
* Helium API is dll for remapping Helium API functions.
* You can get the lastest source code and releases of Helium API at :
* https://github.com/Helium-DevTeam/Helium
* ----------------------------------------------------------------------------------------
* Helium Copyright (C) 2021-2022 HeliumDevTeam
*
* This file is a part of Helium API
*
* Helium API is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium API is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium API.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

#include"HeliumLogger.h"
#include"pch.h"

namespace HeliumAPI {
	typedef int (*debugprintptr)(string);
	typedef int (*createptr)(string);
	typedef int (*deleteptr)(string);
	typedef int (*loggingptr)(string, string);

	int HeliumExtensionDebugPrint(string debugprint) {
		auto rawptr = HeliumAPIMap.at("HeliumExtensionDebugPrint");
		debugprintptr ptr = (debugprintptr)rawptr;
		return ptr(debugprint);
	}
	int CreateExtensionLogger(string name) {
		auto ptr = (createptr)HeliumAPIMap.at("CreateExtLogger");
		return ptr(name);
	}
	int DeleteExtensionLogger(string name) {
		auto ptr = (deleteptr)HeliumAPIMap.at("DeleteExtLogger");
		return ptr(name);
	}
	int ExtensionLogDebug(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerDebug");
		return ptr(loggername, raw);
	}
	int ExtensionLogInfo(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerInfo");
		return ptr(loggername, raw);
	}
	int ExtensionLogWarn(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerWarn");
		return ptr(loggername, raw);
	}
	int ExtensionLogCrit(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerCrit");
		return ptr(loggername, raw);
	}
	int ExtensionLogError(string loggername, string raw) {
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerError");
		return ptr(loggername, raw);
	}
	int ExtensionLog(string loggername, string raw, int level) {
		switch (level)
		{
		case 0:
			return ExtensionLogDebug(loggername, raw);
		case 1:
			return ExtensionLogInfo(loggername, raw);
		case 2:
			return ExtensionLogWarn(loggername, raw);
		case 3:
			return ExtensionLogError(loggername, raw);
		case 4:
			return ExtensionLogCrit(loggername, raw);
		default:
			return ExtensionLogInfo(loggername, raw);
		}
	}
}