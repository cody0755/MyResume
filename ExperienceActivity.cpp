#include "StdAfx.h"
#include "ExperienceActivity.h"
#include "WinOSAdapter.h"
#include "IDDefine.h"
#include "PersonalActivity.h"

ExperienceActivity::ExperienceActivity(void)
{}

ExperienceActivity::~ExperienceActivity(void)
{}

void ExperienceActivity::on_create()
{
	set_view("res/layout/experience.xml");
	View *v = find_view_by_id(id_quit);
	v->connect(click_signal, this, (SLOT_FUNC)&ExperienceActivity::on_quit);
	v = find_view_by_id(id_view_navi);
	anim.set_period(300);
	anim.set_interpolator(*ResourceCreator::instance().get_linear_interpolator());
	anim.set_view(v);
	Point sp(-200, 50);
	Point ep(0, 50);
	anim.set_points(sp, ep);
	anim.start();

	v = find_view_by_id(id_bn_class_personal);
	v->connect(click_signal, this, (SLOT_FUNC)&ExperienceActivity::on_bn_class);
	v = find_view_by_id(id_bn_class_skill);
	v->connect(click_signal, this, (SLOT_FUNC)&ExperienceActivity::on_bn_class);
	v = find_view_by_id(id_bn_class_wanting);
	v->connect(click_signal, this, (SLOT_FUNC)&ExperienceActivity::on_bn_class);
	v = find_view_by_id(id_bn_class_about);
	v->connect(click_signal, this, (SLOT_FUNC)&ExperienceActivity::on_bn_class);
}

void ExperienceActivity::on_destroy()
{

}

bool ExperienceActivity::on_quit(const Event&)
{
	PostQuitMessage(0);
	return true;
}

bool ExperienceActivity::on_bn_class(const Event& e)
{
	Activity *a = NULL;
	View *v = (View*)e.get_signalor();
	switch (v->get_id())
	{
	case id_bn_class_personal:
		a = new PersonalActivity;
		break;
	case id_bn_class_skill:
		break;
	case id_bn_class_wanting:
		break;
	case id_bn_class_about:
		break;
	}
	push(a);
	return true;
}