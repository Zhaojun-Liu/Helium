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

#include"events.h"
namespace Helium {
    deque<HeliumEventInstance*> eventsqueue;
    map<int, HeliumEvent*> eventmap;

    int RegisterHeliumEvent(HeliumEvent* event, int eventnum)
    {
        return 0;
    }

    int DeleteHeliumEvent(int eventnum)
    {
        return 0;
    }

    int GetHeliumEvent(int eventnum, HeliumEvent* event)
    {
        return 0;
    }

    int GetHeliumEventIterator(int eventnum, map<int, HeliumEvent>::iterator* outit)
    {
        return 0;
    }

    int CreateHeliumEvent(int eventnum, int quantity)
    {
        return 0;
    }

    int BlockHeliumEvent(int eventnum)
    {
        return 0;
    }

    HeliumEvent::CallbackFunctionInfo::CallbackFunctionInfo()
    {
    }

    HeliumEvent::HeliumEvent()
    {
    }

    int HeliumEvent::RegisterListenerFunction(HeliumEventCallbackType funcptr)
    {
        return 0;
    }

    HeliumEvent::CallbackFunctionInfo HeliumEvent::GetListenerFunction(LPGUID guid)
    {
        return CallbackFunctionInfo();
    }

    int HeliumEvent::DeleteListenerFunction(LPGUID guid)
    {
        return 0;
    }

    void HeliumEvent::EnableCallback()
    {
    }

    void HeliumEvent::DisableCallback()
    {
    }

    void HeliumEvent::EnableFunctionCallback(LPGUID guid)
    {
    }

    void HeliumEvent::DisableFunctionCallback(LPGUID guid)
    {
    }
}