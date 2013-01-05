#ifndef MYRESUME_SKILLACTIVITY_H
#define MYRESUME_SKILLACTIVITY_H

#include "useless.h"
#include "TranslateViewAnimator.h"

class SkillActivity : public Activity
{
public:
	SkillActivity(void);
	virtual ~SkillActivity(void);

private:
	void on_create();
	void on_destroy();

	bool on_quit(const Event&);
	bool on_bn_class(const Event&);

	TranslateViewAnimator anim;
};

#endif