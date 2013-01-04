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
	colorref text_clr = 0xFFFFFF;
	if (iter != text_clrs.end())
	{
		text_clr = iter->second;
	}

	draw_text(painter, get_text_lines(), text_clr);
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
		colorref clr;
		sscanf(iter->second.c_str(), "%x", &clr);
		set_text_clr(draw_status_enable, clr);
	}
	iter = prop.find("font_disable_color");
	if (iter != iter_end)
	{
		colorref clr;
		sscanf(iter->second.c_str(), "%x", &clr);
		text_clrs[draw_status_disable] = clr;
		set_text_clr(draw_status_disable, clr);
	}
	iter = prop.find("font_pressed_color");
	if (iter != iter_end)
	{
		colorref clr;
		sscanf(iter->second.c_str(), "%x", &clr);
		set_text_clr(draw_status_pressed, clr);
	}
	string font_family;
	iter = prop.find("font_family");
	if (iter != iter_end)
	{
		font_family = iter->second;
	}
	Size size;
	int i = 0;
	iter = prop.find("font_width");
	if (iter != iter_end)
	{
		sscanf(iter->second.c_str(), "%d", &i);
		size.cx = i;
	}
	iter = prop.find("font_height");
	if (iter != iter_end)
	{
		sscanf(iter->second.c_str(), "%d", &i);
		size.cy = i;
	}
	if (size.valid() && !font_family.empty())
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

void TextView::set_text_clr(unsigned long s, colorref c)
{
	text_clrs[s] = c;
	invalidate();
}

const StatusColorMap& TextView::get_text_clr() const
{
	return text_clrs;
}

bool TextView::get_text_clr(unsigned long s, colorref& c) const
{
	StatusColorMap::const_iterator iter = text_clrs.find(s);
	if (iter != text_clrs.end())
	{
		c = iter->second;
		return true;
	}
	return false;
}

vector<string> TextView::get_text_lines() const
{
	vector<string> lines;
	string temp = text;
	size_t pos = 0;
	for (;;)
	{
		size_t pos = temp.find('\n');
		if (pos != string::npos)
		{
			lines.push_back(temp.substr(0, pos));
			if (pos == temp.size() - 1)
			{
				lines.push_back("");
				break;
			}
			temp = temp.substr(pos+1);
		} 
		else
		{
			lines.push_back(temp);
			break;
		}
	}
	return lines;
}

int TextView::get_text_count(const string& rhs) const
{
	return (int)rhs.size();
}

Size TextView::get_text_size(const string& rhs) const
{
	Size s;
	if (rhs.empty() || !font || !font->valid())
	{
		return s;
	}
	Size fs = font->get_size();
	s.cx = fs.cx * static_cast<short>(get_text_count(rhs));
	s.cy = fs.cy;
	return s;
}

void TextView::draw_text(Painter& painter, const vector<string>& lines, colorref clr) const
{
	Point pt;
	if (cx <= 0 || cy <= 0 || lines.empty()|| !font || !font->valid())
	{
		return;
	}

	short space = 0;
	short font_height = font->get_size().cy;
	short height = lines.size() * font_height + (lines.size() - 1) * space;
	switch (get_v_align())
	{
	case align_top:
		pt.y = y;
		break;
	case align_bottom:
		pt.y = y + (cy - height);
		break;
	case align_v_center:
		pt.y = y + (cy - height) / 2;
		break;
	}
	for (size_t i=0; i<lines.size(); ++i)
	{
		Size ts = get_text_size(lines[i]);
		if (ts.cx <= 0 || ts.cy <= 0)
		{
			pt.y += (font_height + space);
			continue;
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
		painter.draw_text(text, pt, *font, clr);
		pt.y += (font_height + space);
	}
}
