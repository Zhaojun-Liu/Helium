#pragma once

#ifndef _H_EXTENSION
#define _H_EXTENSION

#include<string>
#include<vector>
#include<iostream>
#include<map>
#include<Windows.h>
#include<spdlog/spdlog.h>
#include"xmlutils.h"
#include"events.h"
#include"tinyxml2.h"

using namespace std;

namespace Helium {
	class HeliumExtensionConfig {
	public:
		_declspec(property(get = GetExtConfigPath, put = PutExtConfigPath)) string Extconfigpath;
		_declspec(property(get = GetExtName, put = PutExtName)) string Extname;

		string _stdcall GetExtConfigPath() {
			return configpath;
		}
		void _stdcall PutExtConfigPath(string path) {
			this->configpath = path;
		}

		string _stdcall GetExtName() {
			return configpath;
		}
		void _stdcall PutExtName(string path) {
			this->configpath = path;
		}

		int ReadConfig();
	private:
		string configpath;
		string Extname;
	};

	class HeliumExtensionFuncs {
		
	};

	class HeliumExtension {
		friend class HeliumExtensionConfig;
		friend class HeliumExtensionFuncs;

	public:
		int _stdcall LoadExt();
		int _stdcall LockExt();
		int _stdcall UnlockExt();
		int _stdcall UnloadExt();
		int _stdcall SetConfigPath(string path);

		enum ExtStat {
			EXT_STATUS_EMPTY,
			EXT_STATUS_LOADING,
			EXT_STATUS_LOADED,
			EXT_STATUS_UNLOADING,
			EXT_STATUS_LOCKED
		};
	private:
		HeliumExtensionConfig config;
		HeliumExtensionFuncs funcs;
		int extstat;
		vector<HeliumEventInstance*> EventQueue;
	};
}
#endif //!_H_EXTENSION
