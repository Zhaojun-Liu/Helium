#pragma once

#ifndef _H_LOGGER
#define _H_LOGGER

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<direct.h>
#include<string>
#include<ctime>
#define _MEMORYAPI_H_
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<sstream>
#define LOG_DIR "logs"

#pragma region COLORS
#define _WHITE 0x07
#define RED_FOREGROUND FOREGROUND_INTENSITY | FOREGROUND_RED
#define GREEN_FOREGROUND FOREGROUND_INTENSITY | FOREGROUND_GREEN
#define BLUE_FOREGROUND FOREGROUND_INTENSITY | FOREGROUND_BLUE
#define PURPLE_FOREGROUND FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE
#define YELLOW_FOREGEOUND FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED
#define LIME_FOREGROUND FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define ENABLE_TIME_STAMP true
#define DISABLE_TIME_STAMP false
#pragma endregion

using namespace std;


class HeliumOutput {
public:
	_stdcall HeliumOutput();
	int _stdcall info(const char* content);
	int _stdcall warn(const char* content);
	int _stdcall error(const char* content);
	int _stdcall fatal(const char* content);
	int _stdcall write(string outstr);
	void _stdcall setTimeStamp(bool stat);
private:
	bool enableTimeStamp;
	HANDLE hLogFile = NULL;
	int _stdcall out(LPSTR sOut, WCHAR wTextAttribute);
	int _stdcall out(LPCSTR sOut, WCHAR wTextAttribute);
};
typedef HeliumOutput Logger;
#endif // !_H_LOGGER