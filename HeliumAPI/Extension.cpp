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

#include"Extension.h"
#include"pch.h"

namespace HeliumAPI {
	typedef list<any>(*t1)(string);
	typedef string(*t2)(string);
	typedef int(*t3)(string);
	typedef int(*t4)();
	typedef vector<string>(*t5)(int);

	list<any> GetExtensionMetadata(const string& extname) {
		t1 ptr = t1(HeliumAPIMap.at("GetExtensionMetadata"));
		return ptr(extname);
	}
	string GetExtensionDirectory(const string& extname) {
		t2 ptr = t2(HeliumAPIMap.at("GetExtensionDirectory"));
		return ptr(extname);
	}
	string GetExtensionConfigDirectory(const string& extname) {
		t2 ptr = t2(HeliumAPIMap.at("GetExtensionConfigDirectory"));
		return ptr(extname);
	}
	int GetExtensionStatus(const string& extname) {
		t3 ptr = t3(HeliumAPIMap.at("GetExtensionStatus"));
		return ptr(extname);
	}
	int CreateExtension(const string& configpath) {
		t3 ptr = t3(HeliumAPIMap.at("CreateExtension"));
		return ptr(configpath);
	}
	int LoadExtension(const string& extname) {
		t3 ptr = t3(HeliumAPIMap.at("LoadExtension"));
		return ptr(extname);
	}
	int UnloadExtension(const string& extname) {
		t3 ptr = t3(HeliumAPIMap.at("UnloadExtension"));
		return ptr(extname);
	}
	int ReloadExtension(const string& extname) {
		t3 ptr = t3(HeliumAPIMap.at("ReloadExtension"));
		return ptr(extname);
	}
	int LockExtension(const string& extname) {
		t3 ptr = t3(HeliumAPIMap.at("LockExtension"));
		return ptr(extname);
	}
	int UnlockExtension(const string& extname) {
		t3 ptr = t3(HeliumAPIMap.at("UnlockExtension"));
		return ptr(extname);
	}
	int InitializeAllExtension() {
		t4 ptr = t4(HeliumAPIMap.at("InitializeAllExtension"));
		return ptr();
	}
	int ReinitializeAllExtension() {
		t4 ptr = t4(HeliumAPIMap.at("ReinitializeAllExtension"));
		return ptr();
	}
	int LoadAllExtension() {
		t4 ptr = t4(HeliumAPIMap.at("LoadAllExtension"));
		return ptr();
	}
	int UnloadAllExtension() {
		t4 ptr = t4(HeliumAPIMap.at("UnloadAllExtension"));
		return ptr();
	}
	int ReloadAllExtension() {
		t4 ptr = t4(HeliumAPIMap.at("ReloadAllExtension"));
		return ptr();
	}
	int LockAllExtension() {
		t4 ptr = t4(HeliumAPIMap.at("LockAllExtension"));
		return ptr();
	}
	int UnlockAllExtension() {
		t4 ptr = t4(HeliumAPIMap.at("UnlockAllExtension"));
		return ptr();
	}
	vector<string> GetExtensionList(const int& mask = -1) {
		t5 ptr = t5(HeliumAPIMap.at("GetExtensionList"));
		return ptr(mask);
	}
}