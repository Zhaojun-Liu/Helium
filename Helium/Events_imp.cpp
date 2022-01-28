/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
* ----------------------------------------------------------------------------------------
* Helium Copyright (C) 2021-2022 HeliumDevTeam
*
* This file is a part of Helium
*
* Helium is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

module;

#include<map>

#include<guiddef.h>

module Helium.Events;

using namespace std;

namespace Helium {
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