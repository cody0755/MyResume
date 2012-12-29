#include "TranslateViewAnimator.h"


TranslateViewAnimator::TranslateViewAnimator(void)
{}

TranslateViewAnimator::TranslateViewAnimator(int _period, int _repeat, 
	Interpolator *i, View *v, const Point& sp, const Point& ep)
: ViewAnimator(_period, _repeat, i, v)
, start_pt(sp)
, end_pt(ep)
{}

TranslateViewAnimator::~TranslateViewAnimator(void)
{}

void TranslateViewAnimator::update(float f)
{
	if (!view)
	{
		return;
	}
	view->set_x(start_pt.x + static_cast<short>((end_pt.x - start_pt.x) * f));
	view->set_y(start_pt.y + static_cast<short>((end_pt.y - start_pt.y) * f));
}

Animator* TranslateViewAnimator::clone()
{
	return new TranslateViewAnimator(period, repeat, interpolator, view, start_pt, end_pt);
}

bool TranslateViewAnimator::set_points(const Point& sp, const Point& ep)
{
	if (is_started())
	{
		return false;
	}
	start_pt = sp;
	end_pt = ep;
	return true;
}
