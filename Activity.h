#ifndef MYRESUME_ACTIVITY_H
#define MYRESUME_ACTIVITY_H

#include "object.h"
class View;
class Activity : public Object
{
public:
	Activity(int r_id = 0);
	virtual ~Activity(void);

	virtual void on_create() = 0;
	virtual void on_show() = 0;
	virtual void on_hide() = 0;
	virtual void on_destroy() = 0;

	void set_view(const View *v);
	View* get_view() const;

protected:
	View *view;
	int id;
};

#endif

