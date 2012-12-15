#include "StdAfx.h"
#include "CoverActivity.h"
#include "WinOSAdapter.h"

CoverActivity::CoverActivity(void)
: root_view(NULL)
{}

CoverActivity::~CoverActivity(void)
{}

void CoverActivity::on_create()
{
	root_view = new View();
	if (!root_view)
	{
		return;
	}
	set_view(root_view);
	
	SIZE window_size = WinOSAdapter::instance().get_window_size();
	RECT rt = {0, 0, window_size.cx, window_size.cy};
	root_view->set_rect(rt);
	root_view->set_enable(true);
	root_view->set_background_clr(View::status_enable, RGB(166,190,181));
	root_view->set_background_clr(View::status_pressed, RGB(45,212,147));
	root_view->connect(SignalId::click_signal, this, (SLOT_FUNC)&CoverActivity::on_root_view_clicked);
	
	TextView *text_view = new TextView(root_view);
	if (text_view)
	{
		root_view->push_child(text_view);
	}
	RECT rt1 = {100,100,400,400};
	text_view->set_rect(rt1);
	text_view->set_background_clr(View::status_disable, RGB(0xff,0,0));
	text_view->set_text("世界你好!");
	text_view->set_text_clr(View::status_disable, RGB(0,0xff,0));
	SIZE size = {20,20};
	Font *font = new WinFont(size, "宋体");
	text_view->set_font(*font);

	alarm.start(this, (SLOT_FUNC)&CoverActivity::on_time_out, 500, 5);
}

void CoverActivity::on_destroy()
{

}

bool CoverActivity::on_root_view_clicked(const Event& e)
{
	e;
	return true;
}

bool CoverActivity::on_time_out(const Event& e)
{
	e;
	root_view->set_pressed(true);
	return true;
}
