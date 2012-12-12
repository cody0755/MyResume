#ifndef PAINTER_IMPL_H
#define PAINTER_IMPL_H

#include "Object.h"
class Painter_Impl : public Object
{
public:
	Painter_Impl(void);
	virtual ~Painter_Impl(void);

	virtual bool init() = 0;
	virtual void draw_text(const string&, const POINT&) = 0;
	virtual void draw_rect(const RECT&) = 0;
	virtual void draw_color(COLORREF, const RECT&) = 0;
	virtual void update() = 0;
	virtual void invalidate(const RECT&) = 0;
};

#endif