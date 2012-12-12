#include "StdAfx.h"
#include "Event.h"

Event::Event(Object *obj)
: signalor(obj)
{}

Event::~Event(void)
{}

Object* Event::get_signalor() const
{
	return signalor;
}

MouseEvent::MouseEvent(const POINT& pt, Object *obj)
: Event(obj)
, point(pt)
{}

MouseEvent::~MouseEvent()
{}

const POINT& MouseEvent::get_point() const
{
	return point;
}