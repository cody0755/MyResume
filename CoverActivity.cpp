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
	set_view("res/layout/personal.xml");
	View *v = find_view_by_id(id_bn_class_personal);
	v->connect(click_signal, this, (SLOT_FUNC)&CoverActivity::on_quit);
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