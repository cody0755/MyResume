#ifndef MYRESUME_EVENT_H
#define MYRESUME_EVENT_H

#include "IDDefine.h"

class Object;
class Event
{
public:
	Event(UINT s = invalid_signal, Object *obj = NULL, int p = 0);
	virtual ~Event(void);

	Object* get_signalor() const;
	int get_param() const;

private:
	Event(const Event&);
	Event& operator=(const Event&);

	Object *signalor;
	UINT signal;
	int param;
};

class MouseEvent : public Event
{
public:
	MouseEvent(const POINT& pt, UINT s = invalid_signal, Object *obj = NULL, int p = 0);
	~MouseEvent();

	const POINT& get_point() const;
private:
	POINT point;
};

#endif