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

#include"utils.h"
namespace Helium {
    bool _stdcall Split(const std::string& str, std::map<size_t, std::string>& ret, std::string sep) { // https://blog.csdn.net/qq_22186119/article/details/110472493
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

    string stdfuncallconv _stdcall ReplaceString(string rawstr, string deststr, string repstr)
    {
        string text = rawstr;
        int iter = text.find(deststr);
        text.replace(iter, iter + deststr.size(), repstr);
        return text;
    }

    bool stdfuncallconv _stdcall have(string a, string b)
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

    vector<string> _stdcall split(string str, const char* pattern)
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


    list<string> _stdcall splittolist(const string& str, const string& pattern)
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

    string _stdcall makestring(list<string> list_, string spiliter)
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

    string _stdcall makestring(vector<string> list_, string spiliter)
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
}