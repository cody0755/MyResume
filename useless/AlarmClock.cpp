#include "AlarmClock.h"
#include "WinOSAdapter.h"
#include "Define.h"
#include "AlarmClockManager.h"

AlarmClock::AlarmClock(void)
: last_tick_time(0)
, period(0)
, repeat(1)
, is_running(false)
, is_ticking(false)
{}

AlarmClock::~AlarmClock(void)
{
	if (running())
	{
		cancel();
	}
}

bool AlarmClock::start(Object *obj, SLOT_FUNC slot, int p, int r)
{
	if (running())
	{
		return false;
	}
	last_tick_time = WinOSAdapter::instance().get_tick_count();
	period = max(p, 20);
	repeat = r;
	is_running = true;
	connect(timer_timeout_signal, obj, slot);
	AlarmClockManager::instance().push(this);
	return true;
}

bool AlarmClock::cancel()
{
	if (!is_ticking)
	{
		AlarmClockManager::instance().pop(this);
	} 
	return stop();
}

bool AlarmClock::stop()
{
	if (!running())
	{
		return false;
	}
	is_running = false;
	disconnect(timer_timeout_signal);
	return true;
}

bool AlarmClock::running() const
{
	return is_running;
}

bool AlarmClock::tick(int tick_count)
{
	if (!running())
	{
		return false;
	}
	if (tick_count < (last_tick_time + period))
	{
		return false;
	}
	Event e(timer_timeout_signal, this, tick_count);
	is_ticking = true;
	fire_signal(timer_timeout_signal, e);
	is_ticking = false;
	last_tick_time = tick_count;
	if (repeat != ENDLESS
		&& repeat > 0)
	{
		--repeat;
		if (repeat == 0)
		{
			stop();
		}
	}
	return true;
}
