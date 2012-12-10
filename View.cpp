#include "StdAfx.h"
#include "View.h"
#include "DirtyRectManager.h"
#include "Painter.h"

View::View(View *p)
: parent(p)
, x(0)
, y(0)
, cx(0)
, cy(0)
,bgrd_clr(0)
{}

View::~View(void)
{
	View *v = NULL;
	for (size_t i=0; i<childs.size(); ++i)
	{
		v = childs[i];
		if (v)
		{
			delete v;
		}
	}
}

void View::set_parent(View *p)
{
	if (p != parent)
	{
		parent = p;
	}
}

View* View::get_parent() const
{
	return parent;
}

short View::get_x() const
{
	return x;
}

short View::get_y() const
{
	return y;
}

short View::get_width() const
{
	return cx;
}

short View::get_height() const
{
	return cy;
}

RECT View::get_rect() const
{
	RECT rt = {x,y,x + cx,y + cy};
	return rt;
}

void View::set_x(short rhs)
{
	if (rhs == x)
	{
		return;
	}
	x = rhs;
	invalidate();
	short diff = rhs - x;
	View *v;
	for (size_t i=0; i<childs.size(); ++i)
	{
		v = childs[i];
		if (v)
		{
			v->set_x(v->get_x() + diff);
		}
	}
}

void View::set_y(short rhs)
{
	if (rhs == y)
	{
		return;
	}
	y = rhs;
	invalidate();
	short diff = rhs - y;
	View *v;
	for (size_t i=0; i<childs.size(); ++i)
	{
		v = childs[i];
		if (v)
		{
			v->set_y(v->get_y() + diff);
		}
	}
}

void View::set_width(short rhs)
{
	if (rhs == cx)
	{
		return;
	}
	cx = rhs;
	invalidate();
}

void View::set_height(short rhs)
{
	if (rhs == cy)
	{
		return;
	}
	cy = rhs;
	invalidate();
}

void View::set_rect(const RECT& rt)
{
	set_x((short)rt.left);
	set_y((short)rt.top);
	set_width((short)(rt.right - rt.left));
	set_height((short)(rt.bottom - rt.top));
	invalidate();
}

short View::get_relative_x() const
{
	if (!parent)
	{
		return x;
	}
	return x - parent->x;
}

short View::get_relative_y() const
{
	if (!parent)
	{
		return y;
	}
	return y - parent->y;
}

RECT View::get_relative_rect() const
{
	RECT rt = {get_relative_x(), get_relative_y(),
	get_relative_x() + cx, get_relative_y() + cy};
	return rt;
}

void View::set_relative_x(short rhs)
{
	if (!parent)
	{
		set_x(rhs);
		return;
	}
	set_x(parent->x + rhs);
}

void View::set_relative_y(short rhs)
{
	if (!parent)
	{
		set_y(rhs);
		return;
	}
	set_y(parent->y + rhs);
}

void View::set_relative_rect(const RECT& rt)
{
	set_relative_x((short)rt.left);
	set_relative_y((short)rt.top);
	set_width((short)(rt.right - rt.left));
	set_height((short)(rt.bottom - rt.top));
	invalidate();
}

bool View::hit_test(const POINT& pt) const
{
	return (x <= pt.x && (x + cx) >= pt.x
		&& y <= pt.y && (y + cy) >= pt.y);
}

bool View::on_mouse_down(const POINT& pt)
{
	if (!hit_test(pt))
	{
		return false;
	}
	
	View *v;
	for (size_t i=0; i<childs.size(); ++i)
	{
		v = childs[i];
		if (v->on_mouse_down(pt))
		{
			return true;
		}
	}
	
	return fire_signal();
}

bool View::on_mouse_up(const POINT& pt)
{
	return false;
}

void View::draw(Painter &painter)
{
	if (!DirtyRectManager::instance().is_intersecting(get_rect()))
	{
		return;
	}
	painter.draw_color(bgrd_clr, get_rect());
	
	View *v;
	for (size_t i=0; i<childs.size(); ++i)
	{
		v = childs[i];
		if (v)
		{
			v->draw(painter);
		}
	}
}

void View::push_child(ChildViews::iterator pos, View *v)
{
	childs.insert(pos, 1, v);
}

void View::pop_child(ChildViews::iterator pos)
{
	childs.erase(pos);
}

void View::invalidate() const
{
	DirtyRectManager::instance().union_rect(get_rect());
}