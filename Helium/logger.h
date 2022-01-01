#pragma once
#include<spdlog/spdlog.h>
#include<spdlog/sinks/stdout_color_sinks.h>
#include<spdlog/sinks/daily_file_sink.h>
#include<string>
#include<iostream>
namespace Helium {

#define def int _stdcall
#define INVALID_LOGGER NULL

	using namespace std;

	enum HeliumLoggerLevel
	{
		LOG_LEVEL_DEBUG,
		LOG_LEVEL_INFO,
		LOG_LEVEL_WARNING,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_CRITICAL
	};

	class HeliumLogger
	{
	public:
		_declspec(property(get = GetLoggerName, put = SetLoggerName)) string name;

		string GetLoggerName() {
			return this->loggername;
		}
		void SetLoggerName(string n) {
			this->loggername = n;
		}
		
		HeliumLogger(string name);
		~HeliumLogger() {
			this->log->flush();
		}

		HeliumLogger& operator<<(HeliumLoggerLevel n);
		HeliumLogger& operator<<(string s);
		HeliumLogger& operator<<(const char* c);
		HeliumLogger& operator<<(int n);
		HeliumLogger& operator<<(long n);
		HeliumLogger& operator<<(double s);
	protected:
		int loglevel;
		string loggername;
		shared_ptr<spdlog::logger> log;
		shared_ptr<spdlog::logger> filelog;
	};
}

