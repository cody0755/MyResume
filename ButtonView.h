#ifndef MYRESUME_BUTTON_H
#define MYRESUME_BUTTON_H

#include "textview.h"

class ButtonView : public TextView
{
public:
	ButtonView(View *parent = NULL);
	virtual ~ButtonView(void);
};

#endif