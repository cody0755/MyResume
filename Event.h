#ifndef MYRESUME_EVENT_H
#define MYRESUME_EVENT_H

class Object;
class Event
{
public:
	Event(Object *obj = NULL);
	virtual ~Event(void);

	Object* get_signalor() const;

private:
	Object *signalor;
};

class MouseEvent : public Event
{
public:
	MouseEvent(const POINT& pt, Object *obj  = NULL);
	~MouseEvent();

	const POINT& get_point() const;
private:
	POINT point;
};

#endif