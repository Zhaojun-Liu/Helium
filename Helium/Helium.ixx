module;

#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include<thread>
#include<strstream>
#include<iostream>
#include<spdlog/spdlog.h>

#include"logger.h"
#include"parse.h"
#include"config.h"
#include"minecraftserver.h"
#include"extension.h"
#include"initdir.h"
#include"errorexit.h"
#include"versioncontrol.h"
#include"heliumconfig.h"

export module Helium;

export import Helium.CommandQueue;
export import Helium.Commands;
export import Helium.Config;
export import Helium.ErrorExit;
export import Helium.Events;
export import Helium.ExportFunction;
export import Helium.Extension;
export import Helium.InitDirectory;
export import Helium.Logger;
export import Helium.MinecraftServer;
export import Helium.Parser;
export import Helium.Utils;
export import Helium.VersionControl;
export import Helium.XMLUtils;

using namespace std;

export{
	namespace Helium {
		PTP_POOL heliumtp;

		int ProcessServerOutput(MinecraftServerInstance*, string, HANDLE, HANDLE);
		int HeliumMain(int argc, char* argv[]);
		void HeliumInitOutput();
		int HeliumInit();
		int HeliumEnvInit();
		int HeliumFin();
		int HeliumStartServer();
	}
}