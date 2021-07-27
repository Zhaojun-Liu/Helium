#pragma once

#ifndef _H_UTILS
#define _H_UTILS

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#define stdfuncallconv WINAPI

#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<Windows.h>
#include<list>
#include<strstream>
#include<windows.h>

using namespace std;

//用指定字符串{pattern}切片{str}
vector<string> split(const string& str, const string& pattern);

//用指定字符串{pattern}切片{str}
list<string> splittolist(const string& str, const string& pattern);

//从字符串list生成字符串,以指定字符串分隔
string makestring(list<string> list_, string spiliter);

//从字符串vector生成字符串,以指定字符串分隔
string makestring(vector<string> list_, string spiliter);
bool Split(const std::string& str, std::map<size_t, std::string>& ret, std::string sep);
//寻找文件夹是否存在 strpath:目录
//返回true即为文件夹存在 返回false为文件夹不存在或者为文件
bool CheckFolderExist(const string& strPath);

//列出指定路径下的所有文件
vector<string> stdfuncallconv ListFiles(string path);

//列出指定路径下带有指定扩展名的所有文件
vector<string> stdfuncallconv ListFiles(string path, string ext);

//字符串a中含有字符串b
bool stdfuncallconv have(string a, string b);

string stdfuncallconv ReplaceString(string rawstr, string deststr, string repstr);

#endif // !_H_UTILS