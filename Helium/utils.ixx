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