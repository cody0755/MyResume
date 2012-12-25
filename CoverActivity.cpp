#include "StdAfx.h"
#include "CoverActivity.h"
#include "WinOSAdapter.h"

CoverActivity::CoverActivity(void)
{}

CoverActivity::~CoverActivity(void)
{}

void CoverActivity::on_create()
{
	set_view("res/layout/personal.xml");
	View *v = find_view_by_id(id_quit);
	v->connect(click_signal, this, (SLOT_FUNC)&CoverActivity::on_quit);
	v = find_view_by_id(id_view_navi);
	anim.set_period(300);
	anim.set_interpolator(*ResourceCreator::instance().get_linear_interpolator());
	anim.set_view(v);
	POINT sp = {-200, 50};
	POINT ep = {0, 50};
	anim.set_points(sp, ep);
	anim.start();
}

void CoverActivity::on_destroy()
{

}

bool CoverActivity::on_quit(const Event&)
{
	PostQuitMessage(0);
	return true;
}