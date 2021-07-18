#pragma once

#include<string>

#include"tinyxml2-9.0.0/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

bool GetNodePointerByName(XMLElement* pRootEle, const char* strNodeName, XMLElement*& Node);
string GetNodeStringByName(XMLElement* pRootEle, string strNodeName);