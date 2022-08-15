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

#pragma once

#include<boost/function.hpp>
#include"pch.h"

using namespace std;
using namespace boost;

#ifdef HELIUMAPI_EXPORTS
#define HELIUMAPI_API extern "C" _declspec(dllexport)
#else
#define HELIUMAPI_API extern "C" _declspec(dllimport)
#endif

namespace HeliumAPI {
	typedef boost::function<int(const list<any>)> StandardHeliumListener;

	void SetEventName(const int& evevtid, const string& namestr);
	void SetEventDescription(const int& eventid, const string& descstr);
	void DispatchEvent(const int& eventid, list<any>& param);
	void RegisterEventListener(const int& eventid, StandardHeliumListener funcptr);
	string EventIDToDescription(const int& eventid);
	string EventIDToName(const int& eventid);
	void BlockEvent(const int& eventid);
	void UnblockEvent(const int& eventid);
	bool IsEventBlocked(const int& eventid);
	void TraceEvent(const int& eventid);
	void UntraceEvent(const int& eventid);
	bool IsEventTraced(const int& eventid);
}