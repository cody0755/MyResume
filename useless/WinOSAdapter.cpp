#include "WinOSAdapter.h"
#include "Activity.h"
#include "DirtyRectManager.h"
#include "DCPainter_Impl.h"
#include "Painter_Impl.h"
#include "Painter.h"
#include "ActivityManager.h"
#include "AlarmClockManager.h"

extern HWND handle_main_window;

WinOSAdapter::WinOSAdapter(void)
: painter(NULL)
, painter_impl(NULL)
{
	window_size.cx = 1024;
	window_size.cy = 600;
}

WinOSAdapter::~WinOSAdapter(void)
{}

WinOSAdapter& WinOSAdapter::instance()
{
	static WinOSAdapter inst;
	return inst;
}

void WinOSAdapter::on_event(uint msg, WPARAM wParam, LPARAM lParam)
{
	if (ActivityManager::instance().empty())
	{
		return;
	}
	if (msg > WM_MOUSEFIRST
		&& msg < WM_MOUSELAST)
	{
		on_mouse_event(msg, wParam, lParam);
	}
	else if (msg == WM_TIMER)
	{
		on_timer_event(msg, wParam, lParam);
	}

	request_update();
}

void WinOSAdapter::on_mouse_event(uint msg, WPARAM wParam, LPARAM lParam)
{
	Activity *a = ActivityManager::instance().top();
	Point pt(LOWORD(lParam), HIWORD(lParam));
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		a->mouse_down(pt);
		break;
	case WM_LBUTTONUP:
		a->mouse_up(pt);
		break;
	}
}

void WinOSAdapter::on_timer_event(uint msg, WPARAM wParam, LPARAM lParam)
{
	AlarmClockManager::instance().tick(get_tick_count());
}

void WinOSAdapter::request_update()
{
	if (DirtyRectManager::instance().is_none())
	{
		return;
	}
	if (!painter_impl)
	{
		painter_impl = new DCPainter_Impl();
		if (!painter_impl || !painter_impl->init())
		{
			return;
		}
	}
	if (!painter_impl->valid() && !painter_impl->init())
	{
		return;
	}
	if (!painter)
	{
		painter = new Painter(painter_impl);
	}
	if (!painter)
	{
		return;
	}
	painter->invalidate(DirtyRectManager::instance().get_rect());

	Rect window_rect = get_window_rect();
	painter->draw_color(0, window_rect);
	if (ActivityManager::instance().empty())
	{
		DirtyRectManager::instance().clear();
		return;
	}
	Activity *a = ActivityManager::instance().top();
	if (a)
	{
		a->draw_view(*painter);
	}

	painter->update();

	DirtyRectManager::instance().clear();
}

void WinOSAdapter::startup(Activity *first_activity)
{
	if (!first_activity)
	{
		return;
	}
	ActivityManager::instance().push(first_activity);
}

Size WinOSAdapter::get_window_size()
{
	return window_size;
}

Rect WinOSAdapter::get_window_rect()
{
	RECT window_rect = {0};
	GetWindowRect(handle_main_window, &window_rect);
	return Rect(window_rect.left, window_rect.top, 
		window_rect.right - window_rect.left,
		window_rect.bottom - window_rect.top);
}

int WinOSAdapter::get_tick_count()
{
	return GetTickCount();
}
