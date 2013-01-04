#ifndef MYRESUME_EXPERIENCEACTIVITY_H
#define MYRESUME_EXPERIENCEACTIVITY_H

#include "useless.h"
#include "TranslateViewAnimator.h"

class ExperienceActivity : public Activity
{
public:
	ExperienceActivity(void);
	virtual ~ExperienceActivity(void);

private:
	void on_create();
	void on_destroy();

	bool on_quit(const Event&);
	bool on_bn_class(const Event&);

	TranslateViewAnimator anim;
};

#endif