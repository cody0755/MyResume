#ifndef MYRESUME_COVERACTIVITY_H
#define MYRESUME_COVERACTIVITY_H

#include "activity.h"
#include "TranslateViewAnimator.h"

class CoverActivity : public Activity
{
public:
	CoverActivity(void);
	virtual ~CoverActivity(void);

private:
	void on_create();
	void on_destroy();

	bool on_quit(const Event&);

	TranslateViewAnimator anim;
};

#endif