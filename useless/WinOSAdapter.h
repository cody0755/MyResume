#ifndef USELESS_WINWinOSAdapter_H
#define USELESS_WINWinOSAdapter_H

#include <Windows.h>
#include "object.h"

class Painter;
class Painter_Impl;
class Activity;
class WinOSAdapter : public Object
{
public:
	static WinOSAdapter& instance();

	void on_event(uint msg, WPARAM wParam, LPARAM lParam);
	void on_mouse_event(uint msg, WPARAM wParam, LPARAM lParam);
	void on_timer_event(uint msg, WPARAM wParam, LPARAM lParam);
	void request_update();
	void startup(Activity*);
	Size get_window_size();
	Rect get_window_rect();
	int get_tick_count();

private:
	WinOSAdapter(void);
	virtual ~WinOSAdapter(void);

	Painter *painter;
	Painter_Impl *painter_impl;
	Size window_size;
};

#endif