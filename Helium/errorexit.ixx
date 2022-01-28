module;

#include<string>
#include<spdlog/spdlog.h>
#include<iostream>

#include"logger.h"

export module Helium.ErrorExit;

using namespace std;

export{
	namespace Helium {
		void HeliumErrorExit(bool ispause, bool uselogger, string str, ...);
		void HeliumError_exit(bool ispause, bool uselogger, string str, ...);
	}
}