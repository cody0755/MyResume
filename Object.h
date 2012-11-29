#ifndef MYRESUME_OBJECT_H
#define MYRESUME_OBJECT_H
#include <list>
#include <utility>
#include "Slot.h"

using std::list;
using std::pair;

class Event;
typedef list<pair<UINT32, Slot*> > SignalSet;
class Object
{
public:
	Object(void);
	virtual ~Object(void);

	void connect(UINT32, Object *, SLOT_FUNC);
	void disconnect(UINT32);
	void fire_signal(UINT32, const Event&);

protected:
	SignalSet active_signal_set;
};

#endif
