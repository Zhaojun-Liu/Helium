#include"xmlutils.h"

bool GetNodePointerByName(tinyxml2::XMLElement* pRootEle, const char* strNodeName, tinyxml2::XMLElement*& Node)
{
	if (0 == strcmp(strNodeName, pRootEle->Value()))
	{
		Node = pRootEle;
		return true;
	}

	tinyxml2::XMLElement* pEle = pRootEle;
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())
	{
		if (0 != strcmp(pEle->Value(), strNodeName))
		{
			GetNodePointerByName(pEle, strNodeName, Node);
		}
		else
		{
			Node = pEle;
			return true;
		}
	}

	return false;
}//https://blog.csdn.net/masikkk/article/details/14191933?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf

string GetNodeStringByName(tinyxml2::XMLElement* pRootEle, string strNodeName)
{
	tinyxml2::XMLElement* pReadEle;
	if(!GetNodePointerByName(pRootEle, strNodeName.c_str(), pReadEle))
		return pReadEle->GetText();
	else
	{
		string v1;
		v1 = "";
		return v1;
	}
}
