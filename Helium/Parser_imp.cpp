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

#include"parse.h"
namespace Helium {

	VanillaParser::VanillaParser()
	{
	}

	VanillaParser::~VanillaParser()
	{
	}

	void* __stdcall VanillaParser::parse(const char* content)
	{
		return nullptr;
	}

	ServerStarted _stdcall VanillaParser::parseServerStarted(const char* content) {
		ServerStarted e;
		string c = content;
		map<size_t, string> m;
		Split(c, m, " ");
		char* str;
		e.itime = strtol(m.at(6).c_str(), &str, 10);
		return e;
	}
	ServerStart _stdcall VanillaParser::parseServerStart(const char* content) {
		ServerStart e;
		string c = content;
		map<size_t, string> m;
		Split(c, m, ":");
		char* str;
		e.port = strtol(m.at(5).c_str(), &str, 10);
		return e;
	}

}