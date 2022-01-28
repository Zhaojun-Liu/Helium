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
		//用指定字符串{pattern}切片{str}
		vector<string> split(const string& str, const string& pattern);

		//用指定字符串{pattern}切片{str}
		list<string> splittolist(const string& str, const string& pattern);
		vector<string> split(string str, const char* pattern);

		//从字符串list生成字符串,以指定字符串分隔
		string makestring(list<string> list_, string spiliter);

		//从字符串vector生成字符串,以指定字符串分隔
		string makestring(vector<string> list_, string spiliter);
		bool Split(const std::string& str, std::map<size_t, std::string>& ret, std::string sep);

		//字符串a中含有字符串b
		bool have(string a, string b);

		string ReplaceString(string rawstr, string deststr, string repstr);

		int ServerTypeStrToID(string str);
		string ServerTypeIDToStr(int id);
	}
}