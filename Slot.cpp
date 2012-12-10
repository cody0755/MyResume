#include "StdAfx.h"
#include "Slot.h"
#include "Object.h"

Slot::Slot(Object *obj, SLOT_FUNC func)
: host(obj)
, function(func)
{}

Slot::~Slot(void)
{
}

void Slot::set(Object *obj, SLOT_FUNC func)
{
	if (obj != host)
	{
		host = obj;
	}
	if (func != function)
	{
		function = func;
	}
}

bool Slot::fire(const Event& e)
{
	return (host->*function)(e);
}