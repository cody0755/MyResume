#include "Painter.h"
#include "Painter_Impl.h"

Painter::Painter(Painter_Impl *i)
: impl(i)
{
}


Painter::~Painter(void)
{
	if (impl)
	{
		delete impl;
	}
}

void Painter::draw_text(const string& text, const Point& origin, const Font& font, colorref clr)
{
	impl->draw_text(text, origin, font, clr);
}

void Painter::draw_rect(const Rect& rt)
{
	impl->draw_rect(rt);
}

void Painter::draw_color(colorref clr, const Rect& rt)
{
	impl->draw_color(clr, rt);
}

void Painter::update()
{
	impl->update();
}

void Painter::invalidate(const Rect& rt)
{
	impl->invalidate(rt);
}