#ifndef USELESS_TRANSLATEVIEWANIMATOR_H
#define USELESS_TRANSLATEVIEWANIMATOR_H

#include "viewanimator.h"

class TranslateViewAnimator : public ViewAnimator
{
public:
	TranslateViewAnimator(void);
	TranslateViewAnimator(int _period, int _repeat, Interpolator *i, View *v,
		const Point& sp, const Point& ep);
	virtual ~TranslateViewAnimator(void);

	virtual void update(float);
	virtual Animator* clone();

	bool set_points(const Point& sp, const Point& ep);

private:
	TranslateViewAnimator(const TranslateViewAnimator&);
	TranslateViewAnimator& operator=(const TranslateViewAnimator&);

	Point start_pt;
	Point end_pt;
};

#endif
