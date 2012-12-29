#include "DCPainter_Impl.h"
#include "Font.h"
#include "WinOSAdapter.h"

extern HWND handle_main_window;
DCPainter_Impl::DCPainter_Impl(void)
: memory_dc(NULL)
, window_dc(NULL)
, memory_bitmap(NULL)
, clip_rgn(NULL)
{
}

DCPainter_Impl::~DCPainter_Impl(void)
{
	release();
}

bool DCPainter_Impl::valid() const
{
	return memory_dc && window_dc && memory_bitmap;
}

bool DCPainter_Impl::init()
{
	if (valid())
	{
		return true;
	}

	Rect window_rect = WinOSAdapter::instance().get_window_rect();
	if (!window_rect.valid())
	{
		return false;
	}
	window_dc = GetDC(handle_main_window);
	if (window_dc == NULL)
	{
		return false;
	}
	memory_dc = CreateCompatibleDC(window_dc);
	if (memory_dc == NULL)
	{
		ReleaseDC(handle_main_window, window_dc);
		window_dc = NULL;
		return false;
	}
	memory_bitmap = CreateCompatibleBitmap(window_dc, window_rect.cx, window_rect.cy);
	if (memory_bitmap == NULL)
	{
		ReleaseDC(handle_main_window, window_dc);
		window_dc = NULL;
		DeleteDC(memory_dc);
		memory_dc = NULL;
		return false;
	}
	SelectObject(memory_dc, memory_bitmap);
	return true;
}

void DCPainter_Impl::draw_text(const string& text, const Point& origin, const Font& font, colorref clr)
{
	if (text.empty()
		|| !memory_dc
		|| !font.valid())
	{
		return;
	}
	SetBkMode(memory_dc, TRANSPARENT);
	SetTextColor(memory_dc, clr);
	HFONT old_font = (HFONT)SelectObject(memory_dc, (*(WinFont*)&font));
	TextOut(memory_dc, origin.x, origin.y, text.c_str(), (int)text.size());
	SelectObject(memory_dc, old_font);
}

void DCPainter_Impl::draw_rect(const Rect& rt)
{
	if (!rt.valid()
		|| !memory_dc)
	{
		return;
	}
	Rectangle(memory_dc, rt.x, rt.y, rt.x + rt.cx, rt.y + rt.cy);
}

void DCPainter_Impl::draw_color(colorref clr, const Rect& rt)
{
	if (!rt.valid()
		|| !memory_dc)
	{
		return;
	}
	HBRUSH brush = CreateSolidBrush(clr);
	if (!brush)
	{
		return;
	}
	RECT r = {rt.x, rt.y, rt.x + rt.cx, rt.y + rt.cy};
	FillRect(memory_dc, &r, brush);
	DeleteObject(brush);
}

void DCPainter_Impl::update()
{
	Size size = WinOSAdapter::instance().get_window_size();
	if (!memory_dc
		|| !window_dc
		|| !size.valid())
	{
		return;
	}
	BitBlt(window_dc, 0, 0, size.cx,
		size.cy, memory_dc, 0, 0, SRCCOPY);
	if (clip_rgn)
	{
		SelectObject(memory_dc, NULL);
		DeleteObject(clip_rgn);
		clip_rgn = NULL;
	}
}

void DCPainter_Impl::invalidate(const Rect& rt)
{
	RECT r = {rt.x, rt.y, rt.x + rt.cx, rt.y + rt.cy};
	clip_rgn = CreateRectRgnIndirect(&r);
	if (clip_rgn)
	{
		SelectObject(memory_dc, clip_rgn);
	}
}

void DCPainter_Impl::release()
{
	if (memory_bitmap)
	{
		DeleteObject(memory_bitmap);
		memory_bitmap = NULL;
	}
	if (memory_dc)
	{
		DeleteDC(memory_dc);
		memory_dc = NULL;
	}
	if (window_dc)
	{
		ReleaseDC(handle_main_window, window_dc);
		window_dc = NULL;
	}
	if (clip_rgn)
	{
		DeleteObject(clip_rgn);
		clip_rgn = NULL;
	}
}
