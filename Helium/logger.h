#pragma once
#include<spdlog/spdlog.h>
#include<spdlog/sinks/stdout_color_sinks.h>
#include<spdlog/sinks/daily_file_sink.h>
#include<thread>
#include<strstream>
#include<string>
#include<iostream>
namespace Helium {

#define def int _stdcall
#define INVALID_LOGGER NULL

	using namespace std;
	auto heliumdailysink;
	auto heliumconsolesink;

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
		
		HeliumLogger(string name) {
			this->loggername = name;
			try {
				auto console_sink = std::make_shared<spdlog::logger>(name, heliumconsolesink);
				console_sink->set_pattern("[%T][%l]%n > %v");

				auto file_logger = std::make_shared<spdlog::logger>(name, heliumdailysink);

				spdlog::register_logger(console_sink);
				spdlog::register_logger(file_logger);
				this->log = console_sink;
				this->filelog = file_logger;
			}
			catch (const spdlog::spdlog_ex& ex) {
				cout << "Logger initalization failed(" << this->name << ")" << ex.what() << endl;
			}
		}
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

