#pragma once

#ifndef _H_XMLUTILS
#define _H_XMLUTILS

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include<string>
#include<iostream>

#include"tinyxml2.h"

using namespace std;

bool _stdcall GetNodePointerByName(tinyxml2::XMLElement* pRootEle, const char* strNodeName, tinyxml2::XMLElement*& Node);
string _stdcall GetNodeStringByName(tinyxml2::XMLElement* pRootEle, string strNodeName);
#endif // !_H_XMLUTILS