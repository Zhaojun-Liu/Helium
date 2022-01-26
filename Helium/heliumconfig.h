#pragma once

#ifndef _H_HELIUMCONFIG
#define _H_HELIUMCONFIG

#define CFG_FILENAME "HeliumConfig.xml"

#include<string>

#include"tinyxml2/tinyxml2.h"
#include"logger.h"
#include"xmlutils.h"

namespace Helium {
	using namespace tinyxml2;

	int HeliumConfig();

	int ReadHeliumConfig();
	int SaveHeliumConfig();
	int CreateHeliumConfig();
}

#endif // !_H_HELIUMCONFIG
