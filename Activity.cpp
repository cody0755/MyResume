#include "StdAfx.h"
#include "Activity.h"
#include "View.h"

Activity::Activity(int r_id)
: view(NULL)
, id(r_id)
{}

Activity::~Activity(void)
{
	if (view)
	{
		delete view;
	}
}

void Activity::set_view(const View *v)
{
	if (view == v)
	{
		return;
	}
	view = const_cast<View*>(v);
}

View* Activity::get_view() const
{
	return view;
}