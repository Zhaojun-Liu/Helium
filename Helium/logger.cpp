#include "logger.h"
#include<spdlog/fmt/fmt.h>
namespace Helium {

	def Logger::getDebugMode(bool*)
	{

		return 0;
	}

	def Logger::setDebugMode(bool)
	{

		return 0;
	}

	template<typename FormatString, typename... Args>
	def Logger::info(const FormatString& fmt, Args&&... args)
	{
		spdlog::info(fmt, std::forward<Args>(args)...);
		return 0;
	}

	def Logger::debug(const char*)
	{
		return 0;
	}

	def Logger::warn(const char*)
	{
		return 0;
	}

	def Logger::error(const char*)
	{
		return 0;
	}

	def Logger::critical(const char*)
	{
		return 0;
	}
}