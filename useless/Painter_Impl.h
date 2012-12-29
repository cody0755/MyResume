#ifndef PAINTER_IMPL_H
#define PAINTER_IMPL_H

#include "Object.h"
class Font;
class Painter_Impl : public Object
{
public:
	Painter_Impl(void);
	virtual ~Painter_Impl(void);

	virtual bool valid() const = 0;
	virtual bool init() = 0;
	virtual void draw_text(const string&, const Point&, const Font&, colorref) = 0;
	virtual void draw_rect(const Rect&) = 0;
	virtual void draw_color(colorref, const Rect&) = 0;
	virtual void update() = 0;
	virtual void invalidate(const Rect&) = 0;
};

#endif