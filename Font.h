#ifndef MYRESUME_FONT_H
#define MYRESUME_FONT_H

#include "Painter.h"

class Font
{
public:
	Font();
	Font(const SIZE& s, const string&);
	virtual ~Font(void);

	virtual void draw(Painter &painter) = 0;
	virtual bool valid() const;
	const SIZE& get_size() const;
	const string& get_family() const;

	bool operator==(const Font&);
	bool equal(const SIZE& s, const string&) const;

protected:
	SIZE size;
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
	WinFont(const SIZE&, const string&);
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
