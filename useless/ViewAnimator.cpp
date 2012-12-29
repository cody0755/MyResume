#include "ViewAnimator.h"

ViewAnimator::ViewAnimator(void)
: view(NULL)
{}

ViewAnimator::ViewAnimator(int _period, int _repeat, Interpolator *i, View *v)
: Animator(_period, _period, i)
, view(v)
{}

ViewAnimator::~ViewAnimator(void)
{}

bool ViewAnimator::start()
{
	if (!view)
	{
		return false;
	}
	return Animator::start();
}

bool ViewAnimator::set_view(View *v)
{
	if (is_started() || !v)
	{
		return false;
	}
	view = v;
	view->connect(object_destroy_signal, this, SLOT_FUNC(&ViewAnimator::on_view_destroy));
	return true;
}

bool ViewAnimator::on_view_destroy(const Event&)
{
	view = NULL;
	return ViewAnimator::stop();
}