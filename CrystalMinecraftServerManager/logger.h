#pragma once

#ifndef _H_LOGGER
#define _H_LOGGER

#include<string>
#include<ctime>
#include<Windows.h>
#include<Shlwapi.h>
#include<iostream>

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
#pragma endregion

using namespace std;

static bool isInitalized = false;
static string logfilename;
static HANDLE logfilehandle;

int Debug(string out);
int Debug(LPCSTR out);

int Info(string out);
int Info(LPCSTR out);

int Warning(string out);
int Warning(LPCSTR out);

int Error(string out);
int Error(LPCSTR out);

int Fatal(string out);
int Fatal(LPCSTR out);

class LogFile {
public:
	LogFile();
	int operator<< (string outstr);
};

class HeliumOutput {
public:
	int out(LPSTR sOut, WCHAR wTextAttribute);
	int out(LPCSTR sOut, WCHAR wTextAttribute);
private:
	LogFile log;
};

#endif // !_H_LOGGER