module;

#include<string>
#include<vector>
#include<iostream>
#include<map>
#include<spdlog/spdlog.h>
#include<boost/dll.hpp>

#include"xmlutils.h"
#include"events.h"
#include"tinyxml2/tinyxml2.h"
#include"logger.h"

export module Helium.Extension;

using namespace std;

export{
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
		string extname;
	};

	class HeliumExtensionFuncs {

	};

	class HeliumExtension {
		friend class HeliumExtensionConfig;
		friend class HeliumExtensionFuncs;

	public:
		HeliumExtension(string cfgname);
		~HeliumExtension();

		int LoadExt();
		int LockExt();
		int UnlockExt();
		int UnloadExt();
		int ScanEventFunc();
		int SendExportFuncMap();

		enum ExtStat {
			EXT_STATUS_EMPTY,
			EXT_STATUS_LOADING,
			EXT_STATUS_LOADED,
			EXT_STATUS_UNLOADING,
			EXT_STATUS_UNLOADED,
			EXT_STATUS_LOCKED
		};
	private:
		HeliumExtensionConfig config;
		HeliumExtensionFuncs funcs;
		int extstat;
		vector<HeliumEventInstance*> EventQueue;
	};
}