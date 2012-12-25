#include "StdAfx.h"
#include "TextView.h"
#include "ResourceCreator.h"

TextView::TextView(View *parent)
: View(parent)
{
	font = &ResourceCreator::instance().get_none_font();
}

TextView::~TextView(void)
{}

void TextView::draw(Painter &painter)
{
	if (!DirtyRectManager::instance().is_intersecting(get_rect()))
	{
		return;
	}
	View::draw(painter);

	if (!font
		|| !font->valid()
		|| text.empty())
	{
		return;
	}
	StatusColorMap::iterator iter = text_clrs.find(get_draw_status());
	COLORREF text_clr = 0xFFFFFF;
	if (iter != text_clrs.end())
	{
		text_clr = iter->second;
	}
	POINT text_origin = get_text_origin();
	painter.draw_text(text, text_origin, *font, text_clr);
}

void TextView::parse_self(const PropMap& prop)
{
	PropMap::const_iterator iter = prop.begin();
	PropMap::const_iterator iter_end = prop.end();
	iter = prop.find("text");
	if (iter != iter_end)
	{
		text = iter->second;
	}
	iter = prop.find("font_enable_color");
	if (iter != iter_end)
	{
		COLORREF clr;
		sscanf(iter->second.c_str(), "%x", &clr);
		text_clrs[draw_status_enable] = clr;
	}
	iter = prop.find("font_disable_color");
	if (iter != iter_end)
	{
		COLORREF clr;
		sscanf(iter->second.c_str(), "%x", &clr);
		text_clrs[draw_status_disable] = clr;
	}
	iter = prop.find("font_pressed_color");
	if (iter != iter_end)
	{
		COLORREF clr;
		sscanf(iter->second.c_str(), "%x", &clr);
		text_clrs[draw_status_pressed] = clr;
	}
	string font_family;
	iter = prop.find("font_family");
	if (iter != iter_end)
	{
		font_family = iter->second;
	}
	SIZE size = {0};
	iter = prop.find("font_width");
	if (iter != iter_end)
	{
		sscanf(iter->second.c_str(), "%d", &size.cx);
	}
	iter = prop.find("font_height");
	if (iter != iter_end)
	{
		sscanf(iter->second.c_str(), "%d", &size.cy);
	}
	if (size.cx > 0 && size.cy > 0 && !font_family.empty())
	{
		font = &ResourceCreator::instance().get_font(size, font_family);
	}
}

void TextView::set_text(const string& rhs)
{
	if (rhs == text)
	{
		return;
	}
	text = rhs;
	invalidate();
}

const string& TextView::get_text() const
{
	return text;
}

void TextView::set_font(const Font& f)
{
	if (!font
		|| (*font) == f)
	{
		return;
	}
	font = (Font*)&f;
	invalidate();
}

Font& TextView::get_font()
{
	return *font;
}

const Font& TextView::get_font() const
{
	return *font;
}

void TextView::set_text_clr(unsigned long s, COLORREF c)
{
	text_clrs[s] = c;
	invalidate();
}

const StatusColorMap& TextView::get_text_clr() const
{
	return text_clrs;
}

bool TextView::get_text_clr(unsigned long s, COLORREF& c) const
{
	StatusColorMap::const_iterator iter = text_clrs.find(s);
	if (iter != text_clrs.end())
	{
		c = iter->second;
		return true;
	}
	return false;
}

int TextView::get_text_count() const
{
	if (text.empty())
	{
		return 0;
	}
	return text.size();
}

SIZE TextView::get_text_size() const
{
	SIZE s = {0, 0};
	if (text.empty() || !font || !font->valid())
	{
		return s;
	}
	SIZE fs = font->get_size();
	s.cx = fs.cx * static_cast<LONG>(get_text_count());
	s.cy = fs.cy;
	return s;
}

POINT TextView::get_text_origin() const
{
	POINT pt = {0, 0};
	if (cx <= 0 || cy <= 0)
	{
		return pt;
	}
	SIZE ts = get_text_size();
	if (ts.cx <= 0 || ts.cy <= 0)
	{
		return pt;
	}
	switch (get_h_align())
	{
	case align_left:
		pt.x = x;
		break;
	case align_right:
		pt.x = x + (cx - ts.cx);
		break;
	case align_h_center:
		pt.x = x + (cx - ts.cx) / 2;
		break;
	}
	switch (get_v_align())
	{
	case align_top:
		pt.y = y;
		break;
	case align_bottom:
		pt.y = y + (cy - ts.cy);
		break;
	case align_v_center:
		pt.y = y + (cy - ts.cy) / 2;
		break;
	}
	return pt;
}
