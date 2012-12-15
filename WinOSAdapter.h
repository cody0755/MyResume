#ifndef MYRESUME_WINWinOSAdapter_H
#define MYRESUME_WINWinOSAdapter_H

#include "object.h"

class Painter;
class Painter_Impl;
class WinOSAdapter : public Object
{
public:
	static WinOSAdapter& instance();

	void on_event(UINT msg, WPARAM wParam, LPARAM lParam);
	void on_mouse_event(UINT msg, WPARAM wParam, LPARAM lParam);
	void on_timer_event(UINT msg, WPARAM wParam, LPARAM lParam);
	void request_update();
	void startup();
	SIZE get_window_size();
	int get_tick_count();

private:
	WinOSAdapter(void);
	virtual ~WinOSAdapter(void);

	Painter *painter;
	Painter_Impl *painter_impl;
	SIZE window_size;
};

#endif