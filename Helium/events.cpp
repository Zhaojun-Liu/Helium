#include"events.h"

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
