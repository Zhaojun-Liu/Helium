#pragma once

#ifndef _H_XMLUTILS
#define _H_XMLUTILS

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include<string>

#include"tinyxml2.h"

using namespace std;

bool GetNodePointerByName(tinyxml2::XMLElement* pRootEle, const char* strNodeName, tinyxml2::XMLElement*& Node);
string GetNodeStringByName(tinyxml2::XMLElement* pRootEle, string strNodeName);
int CreateConfigFile();

#endif // !_H_XMLUTILS