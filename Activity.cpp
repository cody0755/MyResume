#include "StdAfx.h"
#include "Activity.h"
#include "View.h"
#include "Painter.h"
#include "ActivityManager.h"

Activity::Activity(int r_id)
: view(NULL)
, id(r_id)
{}

Activity::~Activity(void)
{
	if (view)
	{
		delete view;
	}
}

void Activity::mouse_down(const POINT& pt)
{
	if (on_mouse_down(pt)
		|| !view
		|| !view->hit_test(pt))
	{
		return;
	}
	view->on_mouse_down(pt);
}

void Activity::mouse_up(const POINT& pt)
{
	if (on_mouse_up(pt)
		|| !view
		|| !view->hit_test(pt))
	{
		return;
	}
	view->on_mouse_up(pt);
}

bool Activity::on_mouse_down(const POINT& pt)
{
	return false;
}

bool Activity::on_mouse_up(const POINT& pt)
{
	return false;
}

void Activity::push(Activity *a)
{
	ActivityManager::instance().push(a);
}

void Activity::pop()
{
	ActivityManager::instance().pop();
}

void Activity::set_view(const View *v)
{
	if (view == v)
	{
		return;
	}
	view = const_cast<View*>(v);
}

View* Activity::get_view() const
{
	return view;
}

void Activity::draw_view(Painter& painter)
{
	if (!view)
	{
		return;
	}
	view->draw(painter);
}