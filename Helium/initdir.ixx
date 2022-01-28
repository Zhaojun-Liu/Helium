module;

#include<list>
#include<map>
#include<string>

#include"logger.h"
#include"errorexit.h"

export module Helium.InitDirectory;

using namespace std;

export{
	enum HeliumDirectoryInitPolicy {
		HDIP_BLOCKED,
		HDIP_CREATE_WARING,
		HDIP_CREATE_SLIENT,
		HDIP_CREATE_QUIT,
		HDIP_IGNORE_WARING,
		HDIP_IGNORE_SLIENT,
		HDIP_IGNORE_QUIT,
	};
	typedef HeliumDirectoryInitPolicy HDIP;

	struct HeliumDirectory {
		string dirpath;
		string extrahint;
		HeliumDirectoryInitPolicy policy;

		bool operator==(HeliumDirectory dir) {
			if (this->dirpath == dir.dirpath
				&& this->extrahint == dir.extrahint
				&& this->policy == dir.policy) return true;
			return false;
		}
	};

	int InitHeliumDirectory();
	int AddHeliumDirectory(string path, string hint, HeliumDirectoryInitPolicy policy);
	int AddHeliumDirectory(HeliumDirectory* dir);
	int DeleteHeliumDirectory(string path);
	int BlockPolicy(HeliumDirectoryInitPolicy policy);
	int ReplacePolicy(HeliumDirectoryInitPolicy policy, HeliumDirectoryInitPolicy replace);
}