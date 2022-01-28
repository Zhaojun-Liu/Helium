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

#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<list>
#include<strstream>

#include"minecraftserver.h"

export module Helium.Utils;

using namespace std;

export{
	namespace Helium {
		//��ָ���ַ���{pattern}��Ƭ{str}
		vector<string> split(const string& str, const string& pattern);

		//��ָ���ַ���{pattern}��Ƭ{str}
		list<string> splittolist(const string& str, const string& pattern);
		vector<string> split(string str, const char* pattern);

		//���ַ���list�����ַ���,��ָ���ַ����ָ�
		string makestring(list<string> list_, string spiliter);

		//���ַ���vector�����ַ���,��ָ���ַ����ָ�
		string makestring(vector<string> list_, string spiliter);
		bool Split(const std::string& str, std::map<size_t, std::string>& ret, std::string sep);

		//�ַ���a�к����ַ���b
		bool have(string a, string b);

		string ReplaceString(string rawstr, string deststr, string repstr);

		int ServerTypeStrToID(string str);
		string ServerTypeIDToStr(int id);
	}
}