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

#include"Event.h"
#include"pch.h"

namespace HeliumAPI {
	typedef boost::function<int(const list<any>)> StandardHeliumListener;

	typedef void(*SetPtr)(const int&, const string&);
	typedef void(*DispatchPtr)(const int&, list<any>&);
	typedef void(*RegisterPtr)(const int&, StandardHeliumListener);
	typedef string(*GetPtr)(const int&);
	typedef void(*BlockPtr)(const int&);
	typedef bool(*IsPtr)(const int&);

	void SetEventName(const int& eventid, const string& namestr) {
		SetPtr ptr = SetPtr(HeliumAPIMap.at("SetEventName"));
		ptr(eventid, namestr);
	}
	void SetEventDescription(const int& eventid, const string& descstr) {
		SetPtr ptr = SetPtr(HeliumAPIMap.at("SetEventDesc"));
		ptr(eventid, descstr);
	}
	void DispatchEvent(const int& eventid, list<any>& param) {
		DispatchPtr ptr = DispatchPtr(HeliumAPIMap.at("DispatchEvent"));
		ptr(eventid, param);
	}
	void RegisterEventListener(const int& eventid, StandardHeliumListener funcptr) {
		RegisterPtr ptr = RegisterPtr(HeliumAPIMap.at("RegisterEventListner"));
		ptr(eventid, funcptr);
	}
	string EventIDToDescription(const int& eventid) {
		GetPtr ptr = GetPtr(HeliumAPIMap.at("EventIDToDesc"));
		return ptr(eventid);
	}
	string EventIDToName(const int& eventid) {
		GetPtr ptr = GetPtr(HeliumAPIMap.at("EventIDToName"));
		return ptr(eventid);
	}
	void BlockEvent(const int& eventid) {
		BlockPtr ptr = BlockPtr(HeliumAPIMap.at("BlockEvent"));
		ptr(eventid);
	}
	void UnblockEvent(const int& eventid) {
		BlockPtr ptr = BlockPtr(HeliumAPIMap.at("UnblockEvent"));
		ptr(eventid);
	}
	bool IsEventBlocked(const int& eventid) {
		IsPtr ptr = IsPtr(HeliumAPIMap.at("IsEventBlocked"));
		return ptr(eventid);
	}
	void TraceEvent(const int& eventid) {
		BlockPtr ptr = BlockPtr(HeliumAPIMap.at("TraceEvent"));
		ptr(eventid);
	}
	void UntraceEvent(const int& eventid) {
		BlockPtr ptr = BlockPtr(HeliumAPIMap.at("UntraceEvent"));
		ptr(eventid);
	}
	bool IsEventTraced(const int& eventid) {
		IsPtr ptr = IsPtr(HeliumAPIMap.at("IsEventTraced"));
		return ptr(eventid);
	}
}