#ifndef MYRESUME_PERSONALACTIVITY_H
#define MYRESUME_PERSONALACTIVITY_H

#include "useless.h"
#include "TranslateViewAnimator.h"

class PersonalActivity : public Activity
{
public:
	PersonalActivity(void);
	virtual ~PersonalActivity(void);

private:
	void on_create();
	void on_destroy();

	bool on_quit(const Event&);
	bool on_bn_class(const Event&);

	TranslateViewAnimator anim;
};

#endif