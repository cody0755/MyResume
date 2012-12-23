#ifndef MYRESUME_TRANSLATEVIEWANIMATOR_H
#define MYRESUME_TRANSLATEVIEWANIMATOR_H

#include "viewanimator.h"

class TranslateViewAnimator : public ViewAnimator
{
public:
	TranslateViewAnimator(void);
	TranslateViewAnimator(int _period, int _repeat, Interpolator *i, View *v,
		const POINT& sp, const POINT& ep);
	virtual ~TranslateViewAnimator(void);

	virtual void update(float);
	virtual Animator* clone();

	bool set_points(const POINT& sp, const POINT& ep);

private:
	TranslateViewAnimator(const TranslateViewAnimator&);
	TranslateViewAnimator& operator=(const TranslateViewAnimator&);

	POINT start_pt;
	POINT end_pt;
};

#endif
