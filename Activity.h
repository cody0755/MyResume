#ifndef MYRESUME_ACTIVITY_H
#define MYRESUME_ACTIVITY_H

#include "object.h"
#include "View.h"
#include "TextView.h"

class Painter;
class Activity : public Object
{
public:
	Activity(int r_id = 0);
	virtual ~Activity(void);

	virtual void on_create() = 0;
	virtual void on_destroy() = 0;

	void mouse_down(const POINT& pt);
	void mouse_up(const POINT& pt);
	virtual bool on_mouse_down(const POINT& pt);
	virtual bool on_mouse_up(const POINT& pt);

	void push(Activity *);
	void pop();

	void set_view(const View *v);
	View* get_view() const;
	void draw_view(Painter& painter);

protected:
	View *view;
	int id;
};

#endif

