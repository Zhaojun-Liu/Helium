
#pragma once


#pragma once

#define stdfuncallconv WINAPI

#include<vector>
#include<string>
#include<iostream>
#include<Windows.h>
#include<list>
#include<guiddef.h>
#include<strstream>
#include<windows.h>
#include<TlHelp32.h>
#include<Psapi.h>

using namespace std;

//��ָ���ַ���{pattern}��Ƭ{str}
vector<string> split(const string& str, const string& pattern);

//��ָ���ַ���{pattern}��Ƭ{str}
list<string> splittolist(const string& str, const string& pattern);

//���ַ���list�����ַ���,��ָ���ַ����ָ�
string makestring(list<string> list_, string spiliter);

//���ַ���vector�����ַ���,��ָ���ַ����ָ�
string makestring(vector<string> list_, string spiliter);

//Ѱ���ļ����Ƿ���� strpath:Ŀ¼
//����true��Ϊ�ļ��д��� ����falseΪ�ļ��в����ڻ���Ϊ�ļ�
bool CheckFolderExist(const string& strPath);

//��vector��ɾ��ָ����ĳһ��Ԫ�� 
template<class T1, class T2>
vector<T1> del(vector<T1> a, T2 to_be_removed_obj);

//�г�ָ��·���µ������ļ�
vector<string> stdfuncallconv ListFiles(string path);

//�г�ָ��·���´���ָ����չ���������ļ�
vector<string> stdfuncallconv ListFiles(string path, string ext);

//�ַ���a�к����ַ���b
bool stdfuncallconv have(string a, string b);

//����GUID
string stdfuncallconv CreateGuid(GUID* pguid);

//�Ƚ�MCDRCPP�汾
int stdfuncallconv CompareVersion(string Ver1, string Ver2);

//��ȡ�û������ַ�������\nΪ��β
string stdfuncallconv GetInputString();

//��ȡ�û������ַ�
CHAR stdfuncallconv GetInputChar();

HANDLE stdfuncallconv GetProcessHandle(LPCSTR lpName);

string stdfuncallconv ReplaceString(string rawstr, string deststr, string repstr);