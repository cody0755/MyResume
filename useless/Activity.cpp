#include "Activity.h"
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

void Activity::mouse_down(const Point& pt)
{
	if (on_mouse_down(pt)
		|| !view
		|| !view->hit_test(pt))
	{
		return;
	}
	view->on_mouse_down(pt);
}

void Activity::mouse_up(const Point& pt)
{
	if (on_mouse_up(pt)
		|| !view
		|| !view->hit_test(pt))
	{
		return;
	}
	view->on_mouse_up(pt);
}

bool Activity::on_mouse_down(const Point& pt)
{
	return false;
}

bool Activity::on_mouse_up(const Point& pt)
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

void Activity::set_view(const string& file)
{
	XmlParser parser;
	View *v = parser.parse(file);
	set_view(v);
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

View* Activity::find_view_by_id(int rhs)
{
	if (!view)
	{
		return NULL;
	}
	return view->find_view_by_id(rhs);
}