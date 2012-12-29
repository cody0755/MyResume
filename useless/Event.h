#ifndef USELESS_EVENT_H
#define USELESS_EVENT_H

#include "Define.h"

class Object;
class Event
{
public:
	Event(uint s = invalid_signal, Object *obj = NULL, int p = 0);
	virtual ~Event(void);

	Object* get_signalor() const;
	int get_param() const;

private:
	Event(const Event&);
	Event& operator=(const Event&);

	Object *signalor;
	uint signal;
	int param;
};

class MouseEvent : public Event
{
public:
	MouseEvent(const Point& pt, uint s = invalid_signal, Object *obj = NULL, int p = 0);
	~MouseEvent();

	const Point& get_point() const;
private:
	Point point;
};

#endif