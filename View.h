#ifndef MYRESUME_VIEW_H
#define MYRESUME_VIEW_H

#include "Object.h"
#include <map>
#include "SignalId.h"
#include "DirtyRectManager.h"

class Painter;
class View;
typedef vector<View*> ChildViews;
typedef map<unsigned long, COLORREF> StatusColorMap;
class View : public Object
{
protected:
	enum
	{
		status_visible_mask = 1,
		status_enable_mask = 2,
		status_pressed_mask = 6,
	};
	enum
	{
		status_visible = 1,
		status_enable = 2,
		status_pressed = 6,
	};

public:
	enum
	{
		draw_status_disable = status_enable_mask & ~status_enable,
		draw_status_enable = status_enable,
		draw_status_pressed = status_pressed
	};
	View(View *parent = NULL);
	virtual ~View(void);

	void set_parent(View *);
	View* get_parent() const;

	bool is_visible() const;
	void set_visible(bool visible);
	bool is_enable() const;
	void set_enable(bool enable);
	bool is_pressed() const;
	void set_pressed(bool pressed);
	void set_background_clr(unsigned long, COLORREF);
	const StatusColorMap& get_background_clr() const;
	bool get_background_clr(unsigned long, COLORREF&) const;
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
	RECT get_relative_rect() const;
	void set_relative_x(short rhs);
	void set_relative_y(short rhs);
	void set_relative_rect(const RECT& rt);

	bool hit_test(const POINT& pt) const;
	virtual bool on_mouse_down(const POINT& pt);
	virtual bool on_mouse_up(const POINT& pt);

	virtual void draw(Painter &painter);
	virtual void push_child(View *v);
	virtual void pop_child(ChildViews::iterator pos);
	virtual void invalidate() const;

protected:
	//自定义各个状态的优先级
	virtual unsigned long get_draw_status() const;

protected:
	ChildViews childs;
	View *parent;
	//坐标都是以窗口左上为原点的
	//描画时直接用
	short x;
	short y;
	short cx;
	short cy;

	unsigned long status;
	StatusColorMap bg_clrs;
};

#endif
