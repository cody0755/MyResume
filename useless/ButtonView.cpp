#include "ButtonView.h"

ButtonView::ButtonView(View *parent)
: TextView(parent)
{
	set_enable(true);
}

ButtonView::~ButtonView(void)
{}
