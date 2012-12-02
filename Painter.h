#ifndef MYRESUME_PAINTER_H
#define MYRESUME_PAINTER_H
#include <string>
using std::string;

class Painter_Impl;
class Painter
{
public:
	Painter(void);
	virtual ~Painter(void);

	virtual void draw_text(const string&, const POINT&);
	virtual void draw_rect(const RECT&);
	virtual void draw_color(COLORREF, const RECT&);

protected:
	Painter_Impl *impl;
};

#endif
