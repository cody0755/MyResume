#ifndef MYRESUME_PAINTER_H
#define MYRESUME_PAINTER_H
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

	virtual void draw_text(const string&, const POINT&, const Font&, COLORREF clr);
	virtual void draw_rect(const RECT&);
	virtual void draw_color(COLORREF, const RECT&);
	virtual void update();
	virtual void invalidate(const RECT&);

protected:
	Painter_Impl *impl;
};

#endif
