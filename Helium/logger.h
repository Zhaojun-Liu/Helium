#pragma once
#include<spdlog/spdlog.h>
#include<thread>

#define def int _stdcall

using namespace std;
class Logger
{
public:
	Logger()
	{
	}

	~Logger()
	{
	}
	def getDebugMode(bool*);
	def setDebugMode(bool);
	template<typename FormatString, typename... Args>
	def info(const FormatString& fmt, Args&&... args);
	def debug(const char*);
	def warn(const char*);
	def error(const char*);
	def critical(const char*);
private:
	
};



