#ifndef MYRESUME_ALARMCLOCKMANAGER_H
#define MYRESUME_ALARMCLOCKMANAGER_H

#include "object.h"
class AlarmClock;
typedef list<AlarmClock*> AlarmClockList;
class AlarmClockManager : public Object
{
private:
	AlarmClockManager(void);
	virtual ~AlarmClockManager(void);

	friend class AlarmClock;
	void push(AlarmClock*);
	void pop(AlarmClock*);

public:
	static AlarmClockManager& instance();
	void tick(int tick_count);

private:
	AlarmClockList alarms;
};

#endif
