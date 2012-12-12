#include "StdAfx.h"
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

void Painter::draw_text(const string& text, const POINT& origin)
{
	impl->draw_text(text, origin);
}

void Painter::draw_rect(const RECT& rt)
{
	impl->draw_rect(rt);
}

void Painter::draw_color(COLORREF clr, const RECT& rt)
{
	impl->draw_color(clr, rt);
}

void Painter::update()
{
	impl->update();
}

void Painter::invalidate(const RECT& rt)
{
	impl->invalidate(rt);
}