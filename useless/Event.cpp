#include "Event.h"

Event::Event(uint s, Object *obj, int p)
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

MouseEvent::MouseEvent(const Point& pt, uint s, Object *obj, int p)
: Event(s, obj, p)
, point(pt)
{}

MouseEvent::~MouseEvent()
{}

const Point& MouseEvent::get_point() const
{
	return point;
}