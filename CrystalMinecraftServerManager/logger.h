#pragma once

#ifndef _H_LOGGER
#define _H_LOGGER

#include<string>
#include<ctime>
#include<Windows.h>
#include<Shlwapi.h>
#include<iostream>
#include<fstream>
#include<sstream>
#pragma comment(lib,"shlwapi.lib")

#define LOG_DIR "logs"

#pragma region COLORS
#define WHITE 0x07
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
	HeliumOutput();
	int info(const char* content);
	int warn(const char* content);
	int error(const char* content);
	int fatal(const char* content);
	int write(string outstr);
	void setTimeStamp(bool stat);
private:
	bool enableTimeStamp;
	HANDLE hLogFile = NULL;
	int out(LPSTR sOut, WCHAR wTextAttribute);
	int out(LPCSTR sOut, WCHAR wTextAttribute);
};
typedef HeliumOutput Logger;
#endif // !_H_LOGGER