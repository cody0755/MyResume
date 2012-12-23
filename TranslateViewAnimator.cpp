#include "StdAfx.h"
#include "TranslateViewAnimator.h"


TranslateViewAnimator::TranslateViewAnimator(void)
{
	memset(&start_pt, 0, sizeof(start_pt));
	memset(&end_pt, 0, sizeof(end_pt));
}

TranslateViewAnimator::TranslateViewAnimator(int _period, int _repeat, 
	Interpolator *i, View *v, const POINT& sp, const POINT& ep)
: ViewAnimator(_period, _repeat, i, v)
{
	memcpy(&start_pt, &sp, sizeof(sp));
	memcpy(&end_pt, &ep, sizeof(ep));
}

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

bool TranslateViewAnimator::set_points(const POINT& sp, const POINT& ep)
{
	if (is_started())
	{
		return false;
	}
	memcpy(&start_pt, &sp, sizeof(sp));
	memcpy(&end_pt, &ep, sizeof(ep));
	return true;
}
