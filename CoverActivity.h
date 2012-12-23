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

	bool on_root_view_clicked(const Event& e);
	bool on_quit(const Event&);
	bool on_anim_update(const Event&);
	bool on_anim_stop(const Event&);

	View *root_view;
	ButtonView *bn;
	TranslateViewAnimator anim;
};

#endif