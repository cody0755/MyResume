#include "StdAfx.h"
#include "Painter.h"


Painter::Painter(void)
: impl(NULL)
{
}


Painter::~Painter(void)
{
}

void Painter::draw_text(const string& text, const POINT& origin)
{
	//impl->draw_text(text, origin);
}

void Painter::draw_rect(const RECT& rt)
{
	//impl->draw_rect(rt);
}

void Painter::draw_color(COLORREF clr, const RECT& rt)
{
	//impl->draw_color(clr, rt)
}