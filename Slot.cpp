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

void Slot::fire(const Event& e)
{
	(host->*function)(e);
}