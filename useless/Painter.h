#ifndef USELESS_PAINTER_H
#define USELESS_PAINTER_H
#include <string>
#include "Object.h"
using std::string;

class Painter_Impl;
class Font;
class Painter : public Object
{
public:
	Painter(Painter_Impl*);
	virtual ~Painter(void);

	virtual void draw_text(const string&, const Point&, const Font&, colorref clr);
	virtual void draw_rect(const Rect&);
	virtual void draw_color(colorref, const Rect&);
	virtual void update();
	virtual void invalidate(const Rect&);

protected:
	Painter_Impl *impl;
};

#endif
