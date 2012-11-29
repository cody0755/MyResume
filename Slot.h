#ifndef MYRESUME_SLOT_H
#define MYRESUME_SLOT_H

class Object;
class Event;
typedef void (Object::*SLOT_FUNC)(const Event&);
class Slot
{
public:
	Slot(Object *, SLOT_FUNC);
	~Slot(void);

	void set(Object *, SLOT_FUNC);
	void fire(const Event&);

private:
	Object *host;
	SLOT_FUNC function;
};

#endif
