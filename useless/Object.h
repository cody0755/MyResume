#ifndef USELESS_OBJECT_H
#define USELESS_OBJECT_H
#include <list>
#include <vector>
#include <utility>
#include <string>
#include "Define.h"
#include "Slot.h"
#include "Event.h"

using namespace std;

class Slot;
typedef list<pair<uint, Slot*> > SignalSet;
class Object
{
public:
	Object(void);
	virtual ~Object(void);

	void connect(uint, Object *, SLOT_FUNC);
	void disconnect(uint);
	bool fire_signal(uint, const Event&);

protected:
	SignalSet active_signal_set;
};

#endif
