#include "StdAfx.h"
#include "Object.h"

Object::Object(void)
{}

Object::~Object(void)
{
	Event e(object_destroy_signal, this);
	fire_signal(object_destroy_signal, e);

	SignalSet::iterator iter = active_signal_set.begin();
	SignalSet::iterator iter_end = active_signal_set.end();
	for (; iter != iter_end; ++iter)
	{
		delete iter->second;
	}
}

void Object::connect(UINT32 signal, Object *host, SLOT_FUNC func)
{
	SignalSet::iterator iter = active_signal_set.begin();
	SignalSet::iterator iter_end = active_signal_set.end();
	for (;iter != iter_end; ++iter)
	{
		if (iter->first == signal)
		{
			iter->second->set(host, func);
			return;
		}
	}
	Slot *slot = new Slot(host, func);
	if (slot)
	{
		active_signal_set.push_back(std::make_pair(signal, slot));
	}
}

void Object::disconnect(UINT32 signal)
{
	SignalSet::iterator iter = active_signal_set.begin();
	SignalSet::iterator iter_end = active_signal_set.end();
	for (;iter != iter_end; ++iter)
	{
		if (iter->first == signal)
		{
			delete iter->second;
			active_signal_set.erase(iter);
			return;
		}
	}
}

bool Object::fire_signal(UINT32 signal, const Event& event)
{
	SignalSet::iterator iter = active_signal_set.begin();
	SignalSet::iterator iter_end = active_signal_set.end();
	for (;iter != iter_end; ++iter)
	{
		if (iter->first == signal)
		{
			 return iter->second->fire(event);
		}
	}
	return false;
}
