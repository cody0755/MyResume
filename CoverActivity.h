#ifndef MYRESUME_COVERACTIVITY_H
#define MYRESUME_COVERACTIVITY_H

#include "activity.h"
#include "AlarmClock.h"

class CoverActivity : public Activity
{
public:
	CoverActivity(void);
	virtual ~CoverActivity(void);

private:
	void on_create();
	void on_destroy();

	bool on_root_view_clicked(const Event& e);
	bool on_time_out(const Event& e);

	View *root_view;
	AlarmClock alarm;
};

#endif