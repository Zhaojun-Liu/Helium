#include "logger.h"
#include<spdlog/fmt/fmt.h>
namespace Helium {
	auto heliumdailysink = make_shared<spdlog::sinks::daily_file_sink_mt>("./logs/helium_log.txt", 23, 59);
	auto heliumconsolesink = make_shared<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::automatic);

	HeliumLogger::HeliumLogger(string name) {
		this->loggername = name;
		try {
			string logname = name;

			auto console_sink = make_shared<spdlog::logger>(logname, heliumconsolesink);

			logname.clear();
			logname.append(name).append("_filesink");
			auto file_logger = make_shared<spdlog::logger>(logname, heliumdailysink);

			spdlog::register_logger(console_sink);
			spdlog::register_logger(file_logger);
			this->log = console_sink;
			this->filelog = file_logger;
		}
		catch (const spdlog::spdlog_ex& ex) {
			cout << "Logger initalization failed(" << this->name << "), reason : " << ex.what() << endl;
		}
	}

	HeliumLogger& HeliumLogger::operator<<(HeliumLoggerLevel n) {
		this->loglevel = n;
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(string s) {
		switch (this->loglevel) {
		case HeliumLoggerLevel::LOG_LEVEL_DEBUG:
			this->log->debug(s);
			this->filelog->debug(s);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_INFO:
			this->log->info(s);
			this->filelog->info(s);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_WARNING:
			this->log->warn(s);
			this->filelog->warn(s);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_ERROR:
			this->log->error(s);
			this->filelog->error(s);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_CRITICAL:
			this->log->critical(s);
			this->filelog->critical(s);
			break;
		default:
			break;
		}
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(const char* c) {
		switch (this->loglevel) {
		case HeliumLoggerLevel::LOG_LEVEL_DEBUG:
			this->log->debug(c);
			this->filelog->debug(c);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_INFO:
			this->log->info(c);
			this->filelog->info(c);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_WARNING:
			this->log->warn(c);
			this->filelog->warn(c);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_ERROR:
			this->log->error(c);
			this->filelog->error(c);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_CRITICAL:
			this->log->critical(c);
			this->filelog->critical(c);
			break;
		default:
			break;
		}
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(int n) {
		switch (this->loglevel) {
		case HeliumLoggerLevel::LOG_LEVEL_DEBUG:
			this->log->debug(n);
			this->filelog->debug(n);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_INFO:
			this->log->info(n);
			this->filelog->info(n);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_WARNING:
			this->log->warn(n);
			this->filelog->warn(n);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_ERROR:
			this->log->error(n);
			this->filelog->error(n);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_CRITICAL:
			this->log->critical(n);
			this->filelog->critical(n);
			break;
		default:
			break;
		}
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(long n) {
		switch (this->loglevel) {
		case HeliumLoggerLevel::LOG_LEVEL_DEBUG:
			this->log->debug(n);
			this->filelog->debug(n);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_INFO:
			this->log->info(n);
			this->filelog->info(n);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_WARNING:
			this->log->warn(n);
			this->filelog->warn(n);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_ERROR:
			this->log->error(n);
			this->filelog->error(n);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_CRITICAL:
			this->log->critical(n);
			this->filelog->critical(n);
			break;
		default:
			break;
		}
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(double s) {
		switch (this->loglevel) {
		case HeliumLoggerLevel::LOG_LEVEL_DEBUG:
			this->log->debug(s);
			this->filelog->debug(s);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_INFO:
			this->log->info(s);
			this->filelog->info(s);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_WARNING:
			this->log->warn(s);
			this->filelog->warn(s);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_ERROR:
			this->log->error(s);
			this->filelog->error(s);
			break;
		case HeliumLoggerLevel::LOG_LEVEL_CRITICAL:
			this->log->critical(s);
			this->filelog->critical(s);
			break;
		default:
			break;
		}
		return *this;
	}
}