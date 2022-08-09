/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Helium-DevTeam/Helium
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

#define SERVER_TYPE_VANILLA		0
#define SERVER_TYPE_FORGE		1
#define SERVER_TYPE_BUKKIT		2
#define SERVER_TYPE_BUKKIT14	3
#define SERVER_TYPE_BUNGEECORD	4
#define SERVER_TYPE_WATERFALL	5
#define SERVER_TYPE_CAT			6
#define SERVER_TYPE_BETA18		7

#include<map>
#include<vector>
#include<iostream>
#include<list>
#include<strstream>

export module Helium.Utils;

import Helium.MinecraftServer;

import <string>;

using namespace std;

export{
	namespace Helium {
		//从字符串list生成字符串,以指定字符串分隔
		string makestring(list<string> list_, string spiliter);

		//从字符串vector生成字符串,以指定字符串分隔
		string makestring(vector<string> list_, string spiliter);

		//字符串a中含有字符串b
		bool have(string a, string b);

		string ReplaceString(string rawstr, string deststr, string repstr);

		int ServerTypeStrToID(string str);
		string ServerTypeIDToStr(int id);

        string ReplaceString(string rawstr, string deststr, string repstr)
        {
            string text = rawstr;
            auto iter = text.find(deststr);
            text.replace(iter, iter + deststr.size(), repstr);
            return text;
        }

        bool have(string a, string b)
        {
            if (a.find(b) != string::npos)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        string makestring(list<string> list_, string spiliter)
        {
            string result;
            for (auto iter = list_.begin(); iter != list_.end(); iter++)
            {
                result.append(iter->c_str());
                if (iter == list_.end())
                {
                    //在结尾不加分隔符
                }
                else
                {
                    result.append(spiliter);
                }
            }
            return result;
        }

        string makestring(vector<string> list_, string spiliter)
        {
            string result;
            for (auto iter = list_.begin(); iter != list_.end(); iter++)
            {
                result.append(iter->c_str());
                if (iter == list_.end())
                {
                    //在结尾不加分隔符
                }
                else
                {
                    result.append(spiliter);
                }
            }
            return result;
        }

        int ServerTypeStrToID(string str) {
            if (str == "beta18") return SERVER_TYPE_BETA18;
            if (str == "bukkit") return SERVER_TYPE_BUKKIT;
            if (str == "bukkit14") return SERVER_TYPE_BUKKIT14;
            if (str == "bungeecord") return SERVER_TYPE_BUNGEECORD;
            if (str == "cat") return SERVER_TYPE_CAT;
            if (str == "forge") return SERVER_TYPE_FORGE;
            if (str == "vanilla") return SERVER_TYPE_VANILLA;
            if (str == "waterfall") return SERVER_TYPE_WATERFALL;
            return SERVER_TYPE_VANILLA;
        }

        string ServerTypeIDToType(int id) {
            switch (id) {
            case SERVER_TYPE_BETA18:
                return "beta18";
                break;
            case SERVER_TYPE_BUKKIT:
                return "bukkit";
                break;
            case SERVER_TYPE_BUKKIT14:
                return "bukkit14";
                break;
            case SERVER_TYPE_BUNGEECORD:
                return "bungeecord";
                break;
            case SERVER_TYPE_CAT:
                return "cat";
                break;
            case SERVER_TYPE_FORGE:
                return "forge";
                break;
            case SERVER_TYPE_VANILLA:
                return "vanilla";
                break;
            case SERVER_TYPE_WATERFALL:
                return "waterfall";
                break;
            default:
                return "vanilla";
                break;
            }
        }
	}
}