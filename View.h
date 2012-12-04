#ifndef MYRESUME_VIEW_H
#define MYRESUME_VIEW_H

#include "Object.h"

class Painter;
class View;
typedef vector<View*> ChildViews;
class View : public Object
{
public:
	View(View *parent);
	virtual ~View(void);

	void set_parent(View *);
	View* get_parent() const;
	//获得或设置View的绝对坐标（以窗口左上为原点）
	short get_x() const;
	short get_y() const;
	short get_width() const;
	short get_height() const;
	RECT get_rect() const;
	void set_x(short rhs);
	void set_y(short rhs);
	void set_width(short rhs);
	void set_height(short rhs);
	void set_rect(const RECT& rt);
	//再提供一套设置View相对于父View的坐标的接口
	short get_relative_x() const;
	short get_relative_y() const;
	void set_relative_x(short rhs);
	void set_relative_y(short rhs);

	virtual void draw(Painter &painter);
	virtual void push_child(ChildViews::iterator pos, View *v);
	virtual void pop_child(ChildViews::iterator pos);

protected:
	ChildViews childs;
	View *parent;
	//坐标都是以窗口左上为原点的
	//描画时直接用
	short x;
	short y;
	short cx;
	short cy;
};

#endif
