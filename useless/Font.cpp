#include "Font.h"

Font::Font()
{}

Font::Font(const Size& s, const string& f)
: size(s)
, family(f)
{}

Font::~Font(void)
{}

bool Font::valid() const
{
	return (size.cx > 0 && size.cy > 0 && !family.empty());
}

const Size& Font::get_size() const
{
	return size;
}

const string& Font::get_family() const
{
	return family;
}

bool Font::operator ==(const Font& f)
{
	return equal(f.size, f.family);
}

bool Font::equal(const Size& s, const string& f) const
{
	return (size == s && family == f);
}

WinFont::WinFont(const Size& s, const string& f)
: Font(s, f)
, handle(NULL)
{
	create();
}

WinFont::~WinFont()
{
	if (handle)
	{
		DeleteObject(handle);
	}
}

void WinFont::draw(Painter &painter)
{
	
}

bool WinFont::valid() const
{
	return (Font::valid() && handle);
}

WinFont::operator HFONT() const
{
	return handle;
}

bool WinFont::create()
{
	if (!Font::valid())
	{
		return false;
	}
	LOGFONT log_font = {0};
	log_font.lfWidth = size.cx;
	log_font.lfHeight = size.cy;
	memcpy(log_font.lfFaceName, family.c_str(), family.size());
	handle = CreateFontIndirect(&log_font);
	return (handle != NULL);
}