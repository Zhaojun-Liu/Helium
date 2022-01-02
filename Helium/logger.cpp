#include"logger.h"
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
		this->buffer << s;
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(const char* c) {
		this->buffer << c;
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(int n) {
		this->buffer << n;
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(long n) {
		this->buffer << n;
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(double s) {
		this->buffer << s;
		return *this;
	}
	HeliumLogger& HeliumLogger::operator<<(HeliumEndline hendl) {
		switch (this->loglevel) {
		case HeliumLoggerLevel::LL_DBG:
			this->log->debug(this->buffer.str());
			this->filelog->debug(this->buffer.str());
			break;
		case HeliumLoggerLevel::LL_INFO:
			this->log->info(this->buffer.str());
			this->filelog->info(this->buffer.str());
			break;
		case HeliumLoggerLevel::LL_WARN:
			this->log->warn(this->buffer.str());
			this->filelog->warn(this->buffer.str());
			break;
		case HeliumLoggerLevel::LL_ERR:
			this->log->error(this->buffer.str());
			this->filelog->error(this->buffer.str());
			break;
		case HeliumLoggerLevel::LL_CRIT:
			this->log->critical(this->buffer.str());
			this->filelog->critical(this->buffer.str());
			break;
		default:
			break;
		}
		this->buffer.str("");
		return *this;
	}
}