#ifndef USELESS_ANIMATOR_H
#define USELESS_ANIMATOR_H

#include "object.h"
#include "AlarmClock.h"
#include "Interpolator.h"

class Animator : public Object
{
public:
	Animator(void);
	Animator(int _period, int _repeat, Interpolator *i);
	virtual ~Animator(void);

	virtual bool start();
	virtual bool stop();
	virtual void update(float);
	virtual Animator* clone() const;

	bool is_started();
	bool on_timer(const Event&);

	bool set_period(int);
	bool set_repeat(int);
	bool set_interpolator(const Interpolator&);
	float get_fraction() const;

protected:
	enum
	{
		status_none,
		status_started
	};
	enum {ENDLESS = static_cast<int>(-1)};

	virtual void reset();

	void fire_start_signal();
	void fire_update_signal(int tick);
	void fire_stop_signal();

private:
	Animator(const Animator&);
	Animator& operator=(const Animator&);

protected:
	int status;
	int start_time;
	int period;
	int repeat;
	float fraction;
	Interpolator *interpolator;
	bool is_last_frame;

private:
	AlarmClock timer;
};

#endif