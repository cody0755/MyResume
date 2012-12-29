#ifndef USELESS_IDDEFINE_H
#define USELESS_IDDEFINE_H

#include <algorithm>
using namespace std;

//basic data types
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef ulong colorref;

class Point
{
public:
	Point()
	: x(0), y(0)
	{}
	Point(short rx, short ry)
	: x(rx), y(ry)
	{}
	Point(const Point& rhs)
	: x(rhs.x), y(rhs.y)
	{}
	Point& operator=(const Point& rhs)
	{
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
		}
		return *this;
	}
	bool operator==(const Point& rhs) const
	{
		if (this == &rhs)
		{
			return true;
		}
		return x == rhs.x && y == rhs.y;
	}

	short x,y;
};

class Size
{
public:
	Size()
	: cx(0), cy(0)
	{}
	Size(short rcx, short rcy)
	: cx(rcx), cy(rcy)
	{}
	Size(const Size& rhs)
	: cx(rhs.cx), cy(rhs.cy)
	{}
	Size& operator=(const Size& rhs)
	{
		if (this != &rhs)
		{
			cx = rhs.cx;
			cy = rhs.cy;
		}
		return *this;
	}
	bool operator==(const Size& rhs) const
	{
		if (this == &rhs)
		{
			return true;
		}
		return cx == rhs.cx && cy == rhs.cy;
	}
	bool valid() const {return cx > 0 && cy > 0;}

	short cx, cy;
};

class Rect
{
public:
	Rect()
	: x(0), y(0), cx(0), cy(0)
	{}
	Rect(const Point& pt, const Size& sz)
	: x(pt.x), y(pt.y), cx(sz.cx), cy(sz.cy)
	{}
	Rect(short rx, short ry, short rcx, short rcy)
	: x(rx), y(ry), cx(rcx), cy(rcy)
	{}
	Rect(const Rect& rhs)
	: x(rhs.x), y(rhs.y), cx(rhs.cx), cy(rhs.cy)
	{}
	Rect& operator=(const Rect& rhs)
	{
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
			cx = rhs.cx;
			cy = rhs.cy;
		}
		return *this;
	}
	bool operator==(const Rect& rhs) const
	{
		if (this == &rhs)
		{
			return true;
		}
		return (x == rhs.x && y == rhs.y
			&& cx == rhs.cx && cy == rhs.cy);
	}
	bool valid() const
	{
		return cx > 0 && cy > 0;
	}
	bool is_intersecting(const Rect& rhs) const
	{
		if (!valid() || !rhs.valid())
		{
			return false;
		}
		return (rhs.x <= (x + cx)
			&& x <= (rhs.x + rhs.cx)
			&& rhs.y <= (y + cy)
			&& y <= (rhs.y + rhs.cy));
	}
	void union_rect(const Rect& rhs)
	{
		if (!rhs.valid())
		{
			return;
		}
		if (!valid())
		{
			*this = rhs;
			return;
		}
		if ((rhs.x + rhs.cx) > (x + cx))
		{
			cx = rhs.x + rhs.cx - x;
		}
		if ((rhs.y + rhs.cy) > (y + cy))
		{
			cy = rhs.y + rhs.cy - y;
		}
		x = min(x, rhs.x);
		y = min(y, rhs.y);
	}
	void clear()
	{
		x = 0, y = 0, cx = 0, cy = 0;
	}

	short x, y, cx, cy;
};

//signals
enum
{
	invalid_signal = 0,
	object_destroy_signal,
	press_down_signal,
	press_up_signal,
	click_signal,
	timer_timeout_signal,
	animator_start_signal, 
	animator_update_signal,
	animator_stop_signal
};

enum
{
	invalid_view_id
};

#endif