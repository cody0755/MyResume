#ifndef DCPAINTER_IMPL_H
#define DCPAINTER_IMPL_H

#include <Windows.h>
#include "painter_impl.h"
class DCPainter_Impl : public Painter_Impl
{
public:
	DCPainter_Impl(void);
	virtual ~DCPainter_Impl(void);

	virtual bool valid() const;
	virtual bool init();
	virtual void draw_text(const string&, const Point&, const Font&, colorref clr);
	virtual void draw_rect(const Rect&);
	virtual void draw_color(colorref, const Rect&);
	virtual void update();
	virtual void invalidate(const Rect&);
private:
	void release();
private:
	HRGN clip_rgn;
	HDC memory_dc;
	HDC window_dc;
	HBITMAP memory_bitmap;
};

#endif