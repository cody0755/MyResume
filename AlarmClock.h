#ifndef MYRESUME_ALARMCLOCK_H
#define MYRESUME_ALARMCLOCK_H

#include "object.h"

class AlarmClock : public Object
{
public:
	static const int ENDLESS = -1;

	AlarmClock(void);
	virtual ~AlarmClock(void);

	bool start(Object *obj, SLOT_FUNC slot, int p, int r = 1);
	bool cancel();
	bool running() const;

private:
	friend class AlarmClockManager;
	bool tick(int tick_count);
	bool stop();

private:
	int last_tick_time;
	int period;
	int repeat;
	bool is_running;
};

static const int ENDLESS;

#endif