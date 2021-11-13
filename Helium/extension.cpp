#include"extension.h"
namespace Helium {
	int HeliumExtensionConfig::ReadConfig()	{
		tinyxml2::XMLDocument doc;
		if (auto ret = doc.LoadFile(this->configpath.c_str())
			; ret != tinyxml2::XMLError::XML_SUCCESS) {
			spdlog::critical("Failed to load extension config file : " + this->configpath);
			return -1;
		}

		tinyxml2::XMLElement* root = doc.RootElement();
		if (root == NULL) {
			spdlog::critical("Failed to get root element of extension config file : " + this->configpath);
			return -1;
		}
		return 0;
	}
}