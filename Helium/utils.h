#pragma once

#ifndef _H_UTILS
#define _H_UTILS

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#define stdfuncallconv WINAPI

#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<Windows.h>
#include<list>
#include<strstream>
#include<windows.h>

namespace Helium {

	using namespace std;

	//用指定字符串{pattern}切片{str}
	vector<string> _stdcall split(const string& str, const string& pattern);

	//用指定字符串{pattern}切片{str}
	list<string> _stdcall splittolist(const string& str, const string& pattern);
	vector<string> _stdcall split(string str, const char* pattern);

	//从字符串list生成字符串,以指定字符串分隔
	string _stdcall makestring(list<string> list_, string spiliter);

	//从字符串vector生成字符串,以指定字符串分隔
	string _stdcall makestring(vector<string> list_, string spiliter);
	bool _stdcall Split(const std::string& str, std::map<size_t, std::string>& ret, std::string sep);

	//字符串a中含有字符串b
	bool stdfuncallconv _stdcall have(string a, string b);

	string stdfuncallconv _stdcall ReplaceString(string rawstr, string deststr, string repstr);
}
#endif // !_H_UTILS