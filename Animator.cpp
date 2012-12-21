#include "StdAfx.h"
#include "Animator.h"
#include "WinOSAdapter.h"
#include "Interpolator.h"

Animator::Animator(void)
: status(status_none)
, start_time(0)
, period(0)
, repeat(1)
, fraction(0)
, interpolator(NULL)
, is_last_frame(false)
{
}

Animator::Animator(int _period, int _repeat, Interpolator *i)
: status(status_none)
, start_time(0)
, period(_period)
, repeat(_repeat)
, fraction(0)
, interpolator(i)
, is_last_frame(false)
{}

Animator::~Animator(void)
{
	if (is_started())
	{
		stop();
	}
}

bool Animator::start()
{
	if (is_started() || period == 0 || repeat == 0)
	{
		return false;
	}

	if (!timer.start(this, (SLOT_FUNC)&Animator::on_timer, 40, AlarmClock::ENDLESS))
	{
		return false;
	}
	start_time = WinOSAdapter::instance().get_tick_count();
	fire_start_signal();
	status = status_started;
	return true;
}

bool Animator::stop()
{
	if (!is_started())
	{
		return false;
	}

	fire_stop_signal();
	status = status_none;
	return true;
}

void Animator::update(float)
{}

bool Animator::is_started()
{
	return status == status_started;
}

bool Animator::on_timer(const Event& e)
{
	if (is_last_frame)
	{
		is_last_frame = false;
		stop();
		return true;
	}

	int tick = e.get_param();
	float time_fraction = static_cast<float>(tick - start_time) / period;
	time_fraction = min(1.0f, max(time_fraction, 0.0f));
	fraction = interpolator->calc(time_fraction);
	if (fabs(fraction - 1.0f) < FLT_EPSILON)
	{
		fraction = 1.0f;
	}
	update(fraction);
	if ((fraction == 1.0f) && (repeat != ENDLESS) && (--repeat == 0))
	{
		is_last_frame = true;
	}
	fire_update_signal(tick);
	return true;
}

bool Animator::set_period(int p)
{
	if (is_started())
	{
		return false;
	}
	period = p;
	return true;
}

bool Animator::set_repeat(int r)
{
	if (is_started())
	{
		return false;
	}
	repeat = r;
	return true;
}

bool Animator::set_interpolator(const Interpolator& i)
{
	if (is_started())
	{
		return false;
	}
	interpolator = &i;
	return true;
}

float Animator::get_fraction() const
{
	return fraction;
}

void Animator::fire_start_signal()
{
	fire_signal(animator_start_signal, Event(animator_start_signal, this));
}

void Animator::fire_update_signal(int tick)
{
	fire_signal(animator_update_signal, Event(animator_update_signal, this, tick));
}

void Animator::fire_stop_signal()
{
	fire_signal(animator_stop_signal, Event(animator_stop_signal, this));
}
