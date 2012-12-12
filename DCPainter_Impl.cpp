#include "StdAfx.h"
#include "DCPainter_Impl.h"

extern HWND handle_main_window;
DCPainter_Impl::DCPainter_Impl(void)
: memory_dc(NULL)
, window_dc(NULL)
, memory_bitmap(NULL)
, window_width(0)
, window_height(0)
{
}

DCPainter_Impl::~DCPainter_Impl(void)
{
	release();
}

bool DCPainter_Impl::init()
{
	release();

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

void DCPainter_Impl::draw_text(const string& text, const POINT& origin)
{
	if (text.empty()
		|| !memory_dc)
	{
		return;
	}
	TextOut(memory_dc, origin.x, origin.y, text.c_str(), text.size());
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
}

void DCPainter_Impl::invalidate(const RECT& rt)
{
	InvalidateRect(handle_main_window, &rt, FALSE);
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
}
