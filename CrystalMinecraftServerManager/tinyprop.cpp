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
		iRet += ReadFile(hFile, &buf, 1, &irr, NULL);
		iRet += irr;
		if (irr == 0)
			break;
		strBuf += buf;
	}
	CloseHandle(hFile);

	*strOut = strBuf;
	return iRet;
    
}

DWORD writef(const char* fname,string content) {
	DWORD dwRet = 0;
	DeleteFile(fname);
	HANDLE hFile = CreateFile(fname,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		0
	);
	WriteFile(hFile, content.c_str(), content.length() + 1, &dwRet, NULL);
	CloseHandle(hFile);
    return dwRet;
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
	this->table.clear();
	if (!readf(this->filename.c_str(),&content))
	{
		return 0;
	}
	cout << content;

	if (content.find("\r\n") == content.npos)
	{
		auto mp = split(content, "\r\n");
		for (auto it = mp.begin(); it != mp.end(); it++)
		{
			if (it->second[0] == '#')
			{
				//遇到注释，球都不做
			}
			else
			{
				if (it->second.find("=") != it->second.npos) {
					auto mpp = split(it->second, "=");
					pair<string, string> p;
					p.first = mpp.at(0);
					p.second = mpp.at(1);
					this->table.insert(p);
				}
			}
		}
		return 1;
	}
	else
	{
		auto mp = split(content, "\n");
		for (auto it = mp.begin(); it != mp.end(); it++)
		{
			if (it->second[0] == '#')
			{
				//遇到注释，球都不做
			}
			else
			{
				if (it->second.find("=") != it->second.npos) {
					auto mpp = split(it->second, "=");
					pair<string, string> p;
					p.first = mpp.at(0);
					p.second = mpp.at(1);
					this->table.insert(p);
				}
			}
		}
		return 2;
	}
    return 0;
}

DWORD TinyProp::write()
{
	string content;
	for (auto it = this->table.begin(); it != this->table.end(); it++)
	{
		if (it == this->table.end())
		{
			content += it->first;
			content += '=';
			content += it->second;
		}
		else
		{
			content += it->first;
			content += '=';
			content += it->second;
			content += "\r\n";
		}
	}
	DWORD ret = writef(this->filename.c_str(), content);
    return ret;
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
			return 1;
		}
	}
	return NULL;
}
