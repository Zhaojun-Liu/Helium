#pragma once

#ifndef _H_EXTENSION
#define _H_EXTENSION

#include<string>
#include<vector>
#include<iostream>
#include<map>
#include<Windows.h>
#include<guiddef.h>

#include"replxx/replxx.hxx"

#define EXT_STATUS_EMPTY 0
#define EXT_STATUS_LOADING 1
#define EXT_STATUS_LOADED 2
#define EXT_STATUS_UNLOADING 3
#define EXT_STATUS_EXPIRED 4

#define ON_LOAD				0x1
#define ON_INFO				0x10
#define ON_SERVER_LAUNCH	0x1001
#define ON_SERVER_START		0x100
#define ON_SERVER_STARTUP	0x1000
#define ON_SERVER_STOP		0x10000
#define ON_CONSOLE_INPUT	0x100000
#define ON_PLAYER_INFO		0x1000000
#define ON_UNLOAD			0x10000000
#define ON_HELIUM_STOP		0x20000000


#define GET_EXT_FUNCPTR(name) tempptr = GetProcAddress(dllhandle, name);\
if(tempptr == NULL) {\
	cout << "Get extension function pointer failed : " << name << endl;\
	return -1;\
}\
this->extfuncptrcache.push_back(tempptr)
#define awa return 0
#define retstr string ret = "";return ret
#define ins this->extfunccache.insert(p);
#define fd(a,b) p.first = a;p.second = this->GetFuncPtr(b);
using namespace std;

class HeliumExtension {
private:
	string		extname;
	string		extfilename;

	int			extstatus = 0;
	
	GUID		extguid;

	HMODULE		exthandle = NULL;

	map<int,void*>	extfunccache;
	
public:
	_stdcall HeliumExtension();
	_stdcall HeliumExtension(const HeliumExtension* ext);
	_stdcall ~HeliumExtension();

	string _stdcall SetExtName(string name);
	string _stdcall GetExtName();

	string _stdcall SetExtFileName(string name);
	string _stdcall GetExtFileName();

private:
	int    _stdcall SetExtStatus(int stat);
	void* _stdcall GetFuncPtr(const char* UbgDvtcfVY);
public:
	int    _stdcall GetExtStatus();

	int   SetExtGUID(GUID guid);
	int   GetExtGUID(LPGUID lpGuid);

	int    _stdcall LoadExt();
	int    _stdcall UnloadExt(bool forceunload = false);
	int    _stdcall Expire();
};

#endif //!_H_EXTENSION
