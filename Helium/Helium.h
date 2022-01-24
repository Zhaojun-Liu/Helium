/*
* Helium Pre-Alpha 0.6.1
* Copyright (C) 2021-2022 HeliumDevTeam
*
* Helium is a customizable extension system for Minecraft server which is written in C++.
* This project is inspired by the [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged).
* We target to provide a liter, faster, and more customizable choice.
* As a trade-off, we sacrifice its portability and the simplicity of writing extensions.
* (we r sry that we haven't finish the first alpha version yet, if u r interested in our project, we recommend u to use mcdr as a temporary alternative)
* This project is licensed by the GPL-3.0-or-later license.
*
* Very very special thank to contributors of the following projects:
* [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged)
* [kpeeters/tree.hh](https://github.com/kpeeters/tree.hh)
* [leethomason/tinyxml2](https://github.com/leethomason/tinyxml2/)
* [jcwangxp/Crossline](https://github.com/jcwangxp/Crossline/)
*
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
*
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*    This file is part of Helium.
*
*    Helium is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Helium is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#pragma once

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
#include"permissions.h"
#include"initdir.h"
#include"errorexit.h"
#include"versioncontrol.h"

namespace Helium {
/*
��ע:�˴��汾��Ĭ������ https://semver.org/lang/zh-CN/ ���廯�汾���ƹ�淶2.0.0
�汾��ʽ�����汾��.�ΰ汾��.�޶��ţ��汾�ŵ����������£�

���汾�ţ��������˲����ݵ� API �޸ģ�
�ΰ汾�ţ������������¼��ݵĹ�����������
�޶��ţ������������¼��ݵ�����������
���а汾�ż��汾������Ϣ���Լӵ������汾��.�ΰ汾��.�޶��š��ĺ��棬��Ϊ���졣(ժ��semver.org)
*/
#define PROJECT_NAME_STR "Helium"
#define PROJECT_VER_STR "0.6.2"
#define PROJECT_DEVSTAT "Pre-Alpha"
#define NOT_STABLE
#define pass continue;

	using namespace std;

	PTP_POOL heliumtp;

	int ProcessServerOutput(MinecraftServerInstance*, string, HANDLE, HANDLE);
	int HeliumMain(int argc, char* argv[]);
	void HeliumInitOutput();
	int HeliumInit();
	int HeliumEnvInit();
	int HeliumFin();
	int HeliumStartServer();
}