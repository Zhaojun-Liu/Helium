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

#include"tinyxml2/tinyxml2.h"

export module Helium.XMLUtils;

using namespace std;
using namespace tinyxml2;

export{
	namespace Helium {
		bool _stdcall GetNodePointerByName(XMLElement* pRootEle, const char* strNodeName, XMLElement*& Node);
		string _stdcall GetNodeStringByName(XMLElement* pRootEle, string strNodeName);
	}
}