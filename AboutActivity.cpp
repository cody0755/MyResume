#include "StdAfx.h"
#include "AboutActivity.h"
#include "WinOSAdapter.h"
#include "IDDefine.h"
#include "PersonalActivity.h"
#include "ExperienceActivity.h"
#include "WantingActivity.h"
#include "SkillActivity.h"

AboutActivity::AboutActivity(void)
{}

AboutActivity::~AboutActivity(void)
{}

void AboutActivity::on_create()
{
	set_view("res/layout/about.xml");
	View *v = find_view_by_id(id_quit);
	v->connect(click_signal, this, (SLOT_FUNC)&AboutActivity::on_quit);
	v = find_view_by_id(id_view_navi);
	anim.set_period(300);
	anim.set_interpolator(*ResourceCreator::instance().get_linear_interpolator());
	anim.set_view(v);
	Point sp(-200, 50);
	Point ep(0, 50);
	anim.set_points(sp, ep);
	anim.start();

	v = find_view_by_id(id_bn_class_experience);
	v->connect(click_signal, this, (SLOT_FUNC)&AboutActivity::on_bn_class);
	v = find_view_by_id(id_bn_class_skill);
	v->connect(click_signal, this, (SLOT_FUNC)&AboutActivity::on_bn_class);
	v = find_view_by_id(id_bn_class_wanting);
	v->connect(click_signal, this, (SLOT_FUNC)&AboutActivity::on_bn_class);
	v = find_view_by_id(id_bn_class_personal);
	v->connect(click_signal, this, (SLOT_FUNC)&AboutActivity::on_bn_class);
}

void AboutActivity::on_destroy()
{

}

bool AboutActivity::on_quit(const Event&)
{
	PostQuitMessage(0);
	return true;
}

bool AboutActivity::on_bn_class(const Event& e)
{
	Activity *a = NULL;
	View *v = (View*)e.get_signalor();
	switch (v->get_id())
	{
	case id_bn_class_experience:
		a = new ExperienceActivity;
		break;
	case id_bn_class_skill:
		a = new SkillActivity;
		break;
	case id_bn_class_wanting:
		a = new WantingActivity;
		break;
	case id_bn_class_personal:
		a = new PersonalActivity;
		break;
	}
	push(a);
	return true;
}