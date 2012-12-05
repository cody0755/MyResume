#ifndef MYRESUME_PAINTER_H
#define MYRESUME_PAINTER_H
#include <string>
#include "Object.h"
using std::string;

class Painter_Impl;
class Painter : public Object
{
public:
	Painter(Painter_Impl*);
	virtual ~Painter(void);

	virtual void draw_text(const string&, const POINT&);
	virtual void draw_rect(const RECT&);
	virtual void draw_color(COLORREF, const RECT&);
	virtual void update();

protected:
	Painter_Impl *impl;
};

#endif
