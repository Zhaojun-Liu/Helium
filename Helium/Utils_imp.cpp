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

#define SERVER_TYPE_VANILLA		0
#define SERVER_TYPE_FORGE		1
#define SERVER_TYPE_BUKKIT		2
#define SERVER_TYPE_BUKKIT14	3
#define SERVER_TYPE_BUNGEECORD	4
#define SERVER_TYPE_WATERFALL	5
#define SERVER_TYPE_CAT			6
#define SERVER_TYPE_BETA18		7

module Helium.Utils;

import <string>;
import Helium.MinecraftServer;

using namespace std;

namespace Helium {
    bool Split(const std::string& str, std::map<size_t, std::string>& ret, std::string sep) { // https://blog.csdn.net/qq_22186119/article/details/110472493
        if (str.empty()) {
            return false;
        }

        std::string temp;
        std::string::size_type begin = str.find_first_not_of(sep);
        std::string::size_type pos = 0;
        size_t line = 0;
        while (begin != std::string::npos) {
            line += 1;
            pos = str.find(sep, begin);
            if (pos != std::string::npos) {
                temp = str.substr(begin, pos - begin);
                begin = pos + sep.length();
            }
            else {
                temp = str.substr(begin);
                begin = pos;
            }

            if (!temp.empty()) {
                ret[line] = temp;
                temp.clear();
            }
        }
        return true;
    }

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

    vector<string> _stdcall split(const string& str, const string& pattern)
    {
        std::vector<std::string> resVec;
        if ("" == str)
        {
            return resVec;
        }
        //方便截取最后一段数据
        std::string strs;
        strs.append(pattern);

        size_t pos = strs.find(pattern);
        size_t size = strs.size();

        while (pos != std::string::npos)
        {
            std::string x = strs.substr(0, pos);
            if (!x.empty())
                resVec.push_back(x);
            strs = strs.substr(pos + 1, size);
            pos = strs.find(pattern);
        }

        return resVec;
    }

    vector<string> split(string str, const char* pattern)
    {
        std::vector<std::string> resVec;
        if ("" == str)
        {
            return resVec;
        }
        //方便截取最后一段数据
        std::string strs;
        strs.append(pattern);

        size_t pos = strs.find(pattern);
        size_t size = strs.size();

        while (pos != std::string::npos)
        {
            std::string x = strs.substr(0, pos);
            if (!x.empty())
                resVec.push_back(x);
            strs = strs.substr(pos + 1, size);
            pos = strs.find(pattern);
        }

        return resVec;
    }


    list<string> splittolist(const string& str, const string& pattern)
    {
        //const char* convert to char*
        char* strc = new char[strlen(str.c_str()) + 1];
        strcpy(strc, str.c_str());
        list<string> resultList;
        char* tmpStr = strtok(strc, pattern.c_str());
        while (tmpStr != NULL)
        {
            resultList.push_back(string(tmpStr));
            tmpStr = strtok(NULL, pattern.c_str());
        }

        delete[] strc;

        return resultList;
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