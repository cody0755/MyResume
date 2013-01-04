#ifndef MYRESUME_ABOUTACTIVITY_H
#define MYRESUME_ABOUTACTIVITY_H

#include "useless.h"
#include "TranslateViewAnimator.h"

class AboutActivity : public Activity
{
public:
	AboutActivity(void);
	virtual ~AboutActivity(void);

private:
	void on_create();
	void on_destroy();

	bool on_quit(const Event&);
	bool on_bn_class(const Event&);

	TranslateViewAnimator anim;
};

#endif