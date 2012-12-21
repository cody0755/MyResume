#include "StdAfx.h"
#include "Event.h"

Event::Event(UINT s, Object *obj, int p)
: signalor(obj)
, signal(s)
, param(p)
{}

Event::~Event(void)
{}

Object* Event::get_signalor() const
{
	return signalor;
}

int Event::get_param() const
{
	return param;
}

MouseEvent::MouseEvent(const POINT& pt, UINT s, Object *obj, int p)
: Event(s, obj, p)
, point(pt)
{}

MouseEvent::~MouseEvent()
{}

const POINT& MouseEvent::get_point() const
{
	return point;
}