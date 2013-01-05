#ifndef MYRESUME_WANTINGACTIVITY_H
#define MYRESUME_WANTINGACTIVITY_H

#include "useless.h"
#include "TranslateViewAnimator.h"

class WantingActivity : public Activity
{
public:
	WantingActivity(void);
	virtual ~WantingActivity(void);

private:
	void on_create();
	void on_destroy();

	bool on_quit(const Event&);
	bool on_bn_class(const Event&);

	TranslateViewAnimator anim;
};

#endif