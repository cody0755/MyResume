#ifndef MYRESUME_WINWinOSAdapter_H
#define MYRESUME_WINWinOSAdapter_H

#include "object.h"

class WinOSAdapter : public Object
{
public:
	static WinOSAdapter& instance();

	void on_event(UINT msg, WPARAM wParam, LPARAM lParam);
	void on_mouse_event(UINT msg, WPARAM wParam, LPARAM lParam);
	void on_timer_event(UINT msg, WPARAM wParam, LPARAM lParam);
	void request_update();
	void startup();

private:
	WinOSAdapter(void);
	virtual ~WinOSAdapter(void);
};

#endif