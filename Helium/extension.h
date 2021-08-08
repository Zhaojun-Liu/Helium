#pragma once

#ifndef _H_EXTENSION
#define _H_EXTENSION

#include<string>
#include<vector>
#include<iostream>

#include<Windows.h>
#include<guiddef.h>

#include"replxx/replxx.hxx"

#define EXT_STATUS_EMPTY 0
#define EXT_STATUS_LOADING 1
#define EXT_STATUS_LOADED 2
#define EXT_STATUS_UNLOADING 3
#define EXT_STATUS_EXPIRED 4

#define GET_EXT_FUNCPTR(name) tempptr = GetProcAddress(dllhandle, name);\
if(tempptr == NULL) {\
	cout << "Get extension function pointer failed : " << name << endl;\
	return -1;\
}\
this->extfuncptrcache.push_back(tempptr)

using namespace std;

class HeliumExtension {
protected:
	string		extname;
	string		extfilename;

	int			extstatus;
	
	GUID		extguid;

	HMODULE		exthandle;

	vector<FARPROC>	extfuncptrcache;
public:
	_stdcall HeliumExtension();
	_stdcall HeliumExtension(const HeliumExtension* ext);
	_stdcall ~HeliumExtension();

	string _stdcall SetExtName(string name);
	string _stdcall GetExtName();

	string _stdcall SetExtFileName(string name);
	string _stdcall GetExtFileName();

protected:
	int    _stdcall SetExtStatus(int stat);
public:
	int    _stdcall GetExtStatus();

	GUID   _stdcall SetExtGUID(GUID guid);
	GUID   _stdcall GetExtGUID();

	int    _stdcall LoadExt();
	int    _stdcall UnloadExt(bool forceunload = false);
	int    _stdcall Expire();
};

#endif //!_H_EXTENSION
