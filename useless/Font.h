#ifndef USELESS_FONT_H
#define USELESS_FONT_H

#include <Windows.h>
#include "Painter.h"

class Font
{
public:
	Font();
	Font(const Size& s, const string&);
	virtual ~Font(void);

	virtual void draw(Painter &painter) = 0;
	virtual bool valid() const;
	const Size& get_size() const;
	const string& get_family() const;

	bool operator==(const Font&);
	bool equal(const Size& s, const string&) const;

private:
	Font(const Font&);
	Font& operator=(const Font&);

protected:
	Size size;
	string family;
};

class NoneFont : public Font
{
public:
	NoneFont(){}
	virtual ~NoneFont(){}

	virtual void draw(Painter &painter){}
	virtual bool valid(){return false;}
};

class WinFont : public Font
{
public:
	WinFont(const Size&, const string&);
	virtual ~WinFont();

	virtual void draw(Painter &painter);
	virtual bool valid() const;
	operator HFONT() const;

protected:
	bool create();

protected:
	HFONT handle;
};

#endif
