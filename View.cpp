#include "StdAfx.h"
#include "View.h"
#include "Painter.h"
#include "Event.h"

View::View(View *p)
: parent(p)
, x(0)
, y(0)
, cx(0)
, cy(0)
, id(0)
, status(status_visible | draw_status_disable)
, align((align_h_mask & align_h_center) | (align_v_mask & align_v_center))
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

void View::set_id(int i)
{
	id = i;
}

int View::get_id() const
{
	return id;
}

void View::set_h_align(unsigned char a)
{
	if ((align & align_h_mask) == (a & align_h_mask))
	{
		return;
	}
	align = ((align & align_v_mask) | (align_h_mask & a));
	invalidate();
}

unsigned char View::get_h_align() const
{
	return align & align_h_mask;
}

void View::set_v_align(unsigned char a)
{
	if ((align & align_v_mask) == (a & align_v_mask))
	{
		return;
	}
	align = ((align & align_h_mask) | (align_v_mask & a));
	invalidate();
}

unsigned char View::get_v_align() const
{
	return align & align_v_mask;
}

bool View::is_visible() const
{
	return ((status & status_visible_mask) == status_visible);
}

void View::set_visible(bool visible)
{
	if (is_visible() == visible)
	{
		return;
	}
	if (visible)
	{
		status |= status_visible_mask;
	} 
	else
	{
		status &= ~status_visible_mask;
	}
	invalidate();
}

bool View::is_enable() const
{
	return ((status & status_enable_mask) == status_enable);
}

void View::set_enable(bool enable)
{
	if (is_enable() == enable)
	{
		return;
	}
	if (enable)
	{
		status |= status_enable_mask;
	}
	else
	{
		status &= ~status_enable_mask;
	}
	invalidate();
}

bool View::is_pressed() const
{
	return ((status & status_pressed_mask) == status_pressed);
}

void View::set_pressed(bool pressed)
{
	if (is_pressed() == pressed)
	{
		return;
	} 
	if (pressed)
	{
		status |= status_pressed_mask;
	} 
	else
	{
		status &= ~status_pressed_mask;
	}
	invalidate();
}

void View::set_background_clr(unsigned long s, COLORREF clr)
{
	bg_clrs[s] = clr;
	invalidate();
}

const StatusColorMap& View::get_background_clr() const
{
	return bg_clrs;
}

bool View::get_background_clr(unsigned long s, COLORREF& c) const
{
	StatusColorMap::const_iterator iter = bg_clrs.find(s);
	if (iter != bg_clrs.end())
	{
		c = iter->second;
		return true;
	}
	return false;
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
	short diff = rhs - x;
	invalidate();
	x = rhs;
	invalidate();
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
	short diff = rhs - y;
	invalidate();
	y = rhs;
	invalidate();
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
	invalidate();
	cx = rhs;
	invalidate();
}

void View::set_height(short rhs)
{
	if (rhs == cy)
	{
		return;
	}
	invalidate();
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

	if (!is_enable())
	{
		return false;
	}
	set_pressed(true);
	MouseEvent event(pt, press_down_signal, this);
	return fire_signal(press_down_signal, event);
}

bool View::on_mouse_up(const POINT& pt)
{
	if (!hit_test(pt))
	{
		return false;
	}
	
	View *v;
	for (size_t i=0; i<childs.size(); ++i)
	{
		v = childs[i];
		if (v->on_mouse_up(pt))
		{
			return true;
		}
	}

	if (!is_enable())
	{
		return false;
	}
	set_pressed(false);
	MouseEvent event(pt, click_signal, this);
	return fire_signal(click_signal, event);
}

void View::draw(Painter &painter)
{
	if (!DirtyRectManager::instance().is_intersecting(get_rect())
		|| !is_visible())
	{
		return;
	}

	StatusColorMap::iterator iter = bg_clrs.find(get_draw_status());
	if (iter != bg_clrs.end())
	{
		painter.draw_color(iter->second, get_rect());
	}
	
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

void View::push_child(View *v)
{
	childs.push_back(v);
}

void View::pop_child(ChildViews::iterator pos)
{
	childs.erase(pos);
}

void View::invalidate() const
{
	DirtyRectManager::instance().union_rect(get_rect());
}

void View::parse(const PropMap& prop)
{
	PropMap::const_iterator iter = prop.begin();
	PropMap::const_iterator iter_end = prop.end();
	iter = prop.find("x");
	if (iter != iter_end)
	{
		set_x(atoi(iter->second.c_str()));
	}
	iter = prop.find("y");
	if (iter != iter_end)
	{
		set_y(atoi(iter->second.c_str()));
	}
	iter = prop.find("relative_x");
	if (iter != iter_end)
	{
		set_relative_x(atoi(iter->second.c_str()));
	}
	iter = prop.find("relative_y");
	if (iter != iter_end)
	{
		set_relative_y(atoi(iter->second.c_str()));
	}
	iter = prop.find("width");
	if (iter != iter_end)
	{
		set_width(atoi(iter->second.c_str()));
	}
	iter = prop.find("height");
	if (iter != iter_end)
	{
		set_height(atoi(iter->second.c_str()));
	}
	iter = prop.find("id");
	if (iter != iter_end)
	{
		set_id(atoi(iter->second.c_str()));
	}
	iter = prop.find("bg_enable_color");
	if (iter != iter_end)
	{
		COLORREF clr;
		sscanf(iter->second.c_str(), "%x", &clr);
		set_background_clr(draw_status_enable, clr);
	}
	iter = prop.find("bg_disable_color");
	if (iter != iter_end)
	{
		COLORREF clr;
		sscanf(iter->second.c_str(), "%x", &clr);
		set_background_clr(draw_status_disable, clr);
	}
	iter = prop.find("bg_pressed_color");
	if (iter != iter_end)
	{
		COLORREF clr;
		sscanf(iter->second.c_str(), "%x", &clr);
		set_background_clr(draw_status_pressed, clr);
	}
	iter = prop.find("visible");
	if (iter != iter_end)
	{
		set_visible(iter->second != "false");
	}
	iter = prop.find("enable");
	if (iter != iter_end)
	{
		set_enable(iter->second != "false");
	}

	iter = prop.find("h_align");
	if (iter != iter_end)
	{
		if (iter->second == "left")
		{
			set_h_align(align_left);
		} 
		else if (iter->second == "right")
		{
			set_h_align(align_right);
		}
		else if (iter->second == "center")
		{
			set_h_align(align_h_center);
		}
	}

	iter = prop.find("v_align");
	if (iter != iter_end)
	{
		if (iter->second == "top")
		{
			set_v_align(align_top);
		} 
		else if (iter->second == "bottom")
		{
			set_v_align(align_bottom);
		}
		else if (iter->second == "center")
		{
			set_v_align(align_v_center);
		}
	}

	parse_self(prop);
}

void View::parse_self(const PropMap&)
{}

View* View::find_view_by_id(int rhs)
{
	if (rhs == invalid_view_id)
	{
		return NULL;
	}
	if (rhs == id)
	{
		return this;
	}
	View *v = NULL;
	for (size_t i=0; i<childs.size(); ++i)
	{
		v = childs[i]->find_view_by_id(rhs);
		if (v)
		{
			return v;
		}
	}
	return NULL;
}

unsigned long View::get_draw_status() const
{
	unsigned long status_mask = draw_status_enable;
	if (is_pressed())
	{
		status_mask = draw_status_pressed;
	}
	else if (!is_enable())
	{
		status_mask = draw_status_disable;
	}
	return status_mask;
}