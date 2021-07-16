#include "tinyprop.h"	
#pragma region File

DWORD readf(const char* fname,string* strOut) {
	DWORD iRet = 0;
	HANDLE hFile = CreateFile(fname,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		iRet = -1;
		return iRet;
	}
	char buf;
	string strBuf;
	while (true)
	{
		DWORD irr;
		ReadFile(hFile, &buf, 1, &irr, NULL);
		iRet += irr;
		if (irr == 0)
			break;
		strBuf += buf;
	}
	CloseHandle(hFile);

	*strOut = strBuf;
	return iRet;
    
}

int writef(const char* fname,string content) {
    return 0;
}

#pragma endregion
#pragma region Spilt
map<int, string> split(const string& str, const string& pattern)
{
    //const char* convert to char*
    char* strc = new char[strlen(str.c_str()) + 1];
    strcpy(strc, str.c_str());
    map<int, string> result;
    char* tmpStr = strtok(strc, pattern.c_str());
    int i = 0;
    while (tmpStr != NULL)
    {
        pair<int, string> p;
        p.first = i;
        p.second = tmpStr;
        result.insert(p);
        tmpStr = strtok(NULL, pattern.c_str());
    }

    delete[] strc;

    return result;
}

#pragma endregion



TinyProp::TinyProp(const char* fname)
{
    this->filename = fname;
    this->read();
}

TinyProp::~TinyProp()
{
}

int TinyProp::read()
{
	string content;
	if (!readf(this->filename.c_str(),&content))
	{
		return 0;
	}
	if (content.find("\r\n") == content.npos)
	{
		return 2;
	}
	else
	{
		return 1;
	}
    return 0;
}

int TinyProp::write()
{
    return 0;
}

const char* TinyProp::get(const char* name)
{
	for (auto it = this->table.begin();it != this->table.end();it++)
	{
		if (it->first == name)
		{
			 return it->second.c_str();
		}
	}
    return NULL;
}

int TinyProp::set(const char* name, const char* value)
{
	for (auto it = this->table.begin(); it != this->table.end(); it++)
	{
		if (it->first == name)
		{
			this->table[it->first] = value;
			return strlen(value);
		}
	}
	return NULL;
}
