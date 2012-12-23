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
	root_view->set_background_clr(View::draw_status_disable, RGB(166,190,181));
	root_view->set_background_clr(View::draw_status_pressed, RGB(45,212,147));
	
	bn = new ButtonView(root_view);
	if (bn)
	{
		root_view->push_child(bn);
		RECT rt1 = {window_size.cx - 100,window_size.cy - 100,window_size.cx,window_size.cy};
		bn->set_rect(rt1);
		bn->set_background_clr(View::draw_status_enable, RGB(0xff,0,0));
		bn->set_background_clr(View::draw_status_pressed, RGB(0x80,0,0));
		bn->set_text("�˳�");
		bn->set_text_clr(View::draw_status_enable, RGB(0,0xff,0));
		SIZE size = {20,20};
		bn->set_font(ResourceCreator::instance().get_font(size, "����"));

		bn->connect(click_signal, this, (SLOT_FUNC)&CoverActivity::on_quit);
	}

	anim.set_period(500);
	anim.set_interpolator(*ResourceCreator::instance().get_linear_interpolator());
	anim.set_view(bn);
	POINT sp = {-100, -100};
	POINT ep = {window_size.cx - 100, window_size.cy - 100};
	anim.set_points(sp, ep);
	//anim.connect(animator_update_signal, this, (SLOT_FUNC)&CoverActivity::on_anim_update);
	//anim.connect(animator_stop_signal, this, (SLOT_FUNC)&CoverActivity::on_anim_stop);
	anim.start();
}

void CoverActivity::on_destroy()
{

}

bool CoverActivity::on_root_view_clicked(const Event&)
{
	return true;
}

bool CoverActivity::on_quit(const Event&)
{
	PostQuitMessage(0);
	return true;
}

bool CoverActivity::on_anim_update(const Event&)
{
	static int end = bn->get_x();
	bn->set_x(static_cast<short>(end * anim.get_fraction()));
	return true;
}

bool CoverActivity::on_anim_stop(const Event&)
{
	return true;
}