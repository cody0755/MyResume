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
	StatusColorMap::iterator iter = text_clrs.find(get_current_status());
	COLORREF text_clr = 0xFFFFFF;
	if (iter != text_clrs.end())
	{
		text_clr = iter->second;
	}
	POINT text_origin = {x, y};
	painter.draw_text(text, text_origin, *font, text_clr);
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
