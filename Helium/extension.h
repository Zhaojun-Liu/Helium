#pragma once

#ifndef _H_EXTENSION
#define _H_EXTENSION

#include<string>
#include<vector>

#include<Windows.h>
#include<guiddef.h>

#include"replxx/replxx.hxx"

#define EXT_STATUS_EMPTY 0
#define EXT_STATUS_LOADING 1
#define EXT_STATUS_LOADED 2
#define EXT_STATUS_UNLOADING 3
#define EXT_STATUS_EXPIRED 4
#define awa return 0
#define retstr string ret = "";return ret
using namespace std;

class HeliumExtension {
protected:
	string		extname;
	string		extfilename;

	int			extstatus;
	
	GUID		extguid;
public:
	HeliumExtension();
	HeliumExtension(const HeliumExtension* ext);
	~HeliumExtension();

	string SetExtName(string name);
	string GetExtName();

	string SetExtFileName(string name);
	string GetExtFileName();

protected:
	int    SetExtStatus(int stat);
public:
	int    GetExtStatus();

	int   SetExtGUID(GUID guid);
	int   GetExtGUID(LPGUID lpGuid);

	int    LoadExt();
	int    UnloadExt(bool forceunload = false);
	int    Expire();
};

#endif //!_H_EXTENSION
