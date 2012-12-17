#include "StdAfx.h"
#include "DCPainter_Impl.h"
#include "Font.h"

extern HWND handle_main_window;
DCPainter_Impl::DCPainter_Impl(void)
: memory_dc(NULL)
, window_dc(NULL)
, memory_bitmap(NULL)
, window_width(0)
, window_height(0)
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

	RECT window_rect = {0};
	GetWindowRect(handle_main_window, &window_rect);
	window_width = window_rect.right - window_rect.left;
	window_height = window_rect.bottom - window_rect.top;
	if (window_width <= 0
		|| window_height <= 0)
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
	memory_bitmap = CreateCompatibleBitmap(window_dc, window_width, window_height);
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

void DCPainter_Impl::draw_text(const string& text, const POINT& origin, const Font& font, COLORREF clr)
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

void DCPainter_Impl::draw_rect(const RECT& rt)
{
	if (rt.right - rt.left <= 0
		|| rt.bottom - rt.top <= 0
		|| !memory_dc)
	{
		return;
	}
	Rectangle(memory_dc, rt.left, rt.top, rt.right, rt.bottom);
}

void DCPainter_Impl::draw_color(COLORREF clr, const RECT& rt)
{
	if (rt.right - rt.left <= 0
		|| rt.bottom - rt.top <= 0
		|| !memory_dc)
	{
		return;
	}
	HBRUSH brush = CreateSolidBrush(clr);
	if (!brush)
	{
		return;
	}
	FillRect(memory_dc, &rt, brush);
	DeleteObject(brush);
}

void DCPainter_Impl::update()
{
	if (!memory_dc
		|| !window_dc
		|| window_width <= 0
		|| window_height <= 0)
	{
		return;
	}
	BitBlt(window_dc, 0, 0, window_width,
		window_height, memory_dc, 0, 0, SRCCOPY);
	if (clip_rgn)
	{
		SelectObject(memory_dc, NULL);
		DeleteObject(clip_rgn);
		clip_rgn = NULL;
	}
}

void DCPainter_Impl::invalidate(const RECT& rt)
{
	clip_rgn = CreateRectRgnIndirect(&rt);
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
