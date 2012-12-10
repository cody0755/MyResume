#ifndef DCPAINTER_IMPL_H
#define DCPAINTER_IMPL_H

#include "painter_impl.h"
class DCPainter_Impl : public Painter_Impl
{
public:
	DCPainter_Impl(void);
	virtual ~DCPainter_Impl(void);

	virtual bool init();
	virtual void draw_text(const string&, const POINT&);
	virtual void draw_rect(const RECT&);
	virtual void draw_color(COLORREF, const RECT&);
	virtual void update();
private:
	void release();
private:
	HDC memory_dc;
	HDC window_dc;
	HBITMAP memory_bitmap;
	int window_width;
	int window_height;
};

#endif