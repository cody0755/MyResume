#include "StdAfx.h"
#include "WinOSAdapter.h"
#include "Activity.h"
#include "DirtyRectManager.h"
#include "DCPainter_Impl.h"
#include "Painter_Impl.h"
#include "Painter.h"
#include "ActivityManager.h"

extern HWND handle_main_window;

WinOSAdapter::WinOSAdapter(void)
{
}

WinOSAdapter::~WinOSAdapter(void)
{}

WinOSAdapter& WinOSAdapter::instance()
{
	static WinOSAdapter inst;
	return inst;
}

void WinOSAdapter::on_event(UINT msg, WPARAM wParam, LPARAM lParam)
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

void WinOSAdapter::on_mouse_event(UINT msg, WPARAM wParam, LPARAM lParam)
{
	Activity *a = ActivityManager::instance().top();
	POINT pt = {LOWORD(lParam), HIWORD(lParam)};
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

void WinOSAdapter::on_timer_event(UINT msg, WPARAM wParam, LPARAM lParam)
{

}

void WinOSAdapter::request_update()
{
	if (DirtyRectManager::instance().is_none())
	{
		return;
	}
	Painter_Impl *impl = new DCPainter_Impl();
	if (!impl || !impl->init())
	{
		return;
	}
	Painter painter(impl);
	painter.invalidate(DirtyRectManager::instance().get_rect());

	RECT window_rect = {0};
	GetWindowRect(handle_main_window, &window_rect);
	painter.draw_color(0, window_rect);
	if (ActivityManager::instance().empty())
	{
		DirtyRectManager::instance().clear();
		return;
	}
	Activity *a = ActivityManager::instance().top();
	if (a)
	{
		a->draw_view(painter);
	}

	painter.update();

	DirtyRectManager::instance().clear();
}
