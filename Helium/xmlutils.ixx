module;

#include<string>
#include<iostream>

#include"tinyxml2/tinyxml2.h"

export module Helium.XMLUtils;

using namespace std;
using namespace tinyxml2;

export{
	bool _stdcall GetNodePointerByName(XMLElement* pRootEle, const char* strNodeName, XMLElement*& Node);
	string _stdcall GetNodeStringByName(XMLElement* pRootEle, string strNodeName);
}