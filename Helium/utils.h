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

//��ָ���ַ���{pattern}��Ƭ{str}
vector<string> split(const string& str, const string& pattern);

//��ָ���ַ���{pattern}��Ƭ{str}
list<string> splittolist(const string& str, const string& pattern);

//���ַ���list�����ַ���,��ָ���ַ����ָ�
string makestring(list<string> list_, string spiliter);

//���ַ���vector�����ַ���,��ָ���ַ����ָ�
string makestring(vector<string> list_, string spiliter);
bool Split(const std::string& str, std::map<size_t, std::string>& ret, std::string sep);
//Ѱ���ļ����Ƿ���� strpath:Ŀ¼
//����true��Ϊ�ļ��д��� ����falseΪ�ļ��в����ڻ���Ϊ�ļ�
bool CheckFolderExist(const string& strPath);

//�г�ָ��·���µ������ļ�
vector<string> stdfuncallconv ListFiles(string path);

//�г�ָ��·���´���ָ����չ���������ļ�
vector<string> stdfuncallconv ListFiles(string path, string ext);

//�ַ���a�к����ַ���b
bool stdfuncallconv have(string a, string b);

string stdfuncallconv ReplaceString(string rawstr, string deststr, string repstr);

#endif // !_H_UTILS