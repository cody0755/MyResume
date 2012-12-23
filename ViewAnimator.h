#ifndef MYRESUME_VIEWANIMATOR_H
#define MYRESUME_VIEWANIMATOR_H

#include "animator.h"
#include "View.h"

class ViewAnimator : public Animator
{
public:
	ViewAnimator(void);
	ViewAnimator(int _period, int _repeat, Interpolator *i, View *v);
	virtual ~ViewAnimator(void);

	virtual bool start();
	virtual bool set_view(View *v);

	bool on_view_destroy(const Event&);

private:
	ViewAnimator(const ViewAnimator&);
	ViewAnimator& operator=(const ViewAnimator&);

protected:
	View *view;
};

#endif
