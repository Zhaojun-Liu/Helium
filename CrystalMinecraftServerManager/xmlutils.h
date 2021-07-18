#pragma once

#include<string>

#include"tinyxml2.h"

using namespace std;

bool GetNodePointerByName(tinyxml2::XMLElement* pRootEle, const char* strNodeName, tinyxml2::XMLElement*& Node);
string GetNodeStringByName(tinyxml2::XMLElement* pRootEle, string strNodeName);
int CreateConfigFile();