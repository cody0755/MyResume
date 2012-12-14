#include "StdAfx.h"
#include "ResourceCreator.h"

ResourceCreator::ResourceCreator(void)
: none_font(NULL)
{}

ResourceCreator::~ResourceCreator(void)
{
	if (none_font)
	{
		delete none_font;
	}
	Font *f;
	for (size_t i=0; i<fonts.size(); ++i)
	{
		f = fonts[i];
		if (f)
		{
			delete f;
		}
	}
	fonts.clear();
}

ResourceCreator& ResourceCreator::instance()
{
	static ResourceCreator inst;
	return inst;
}

NoneFont& ResourceCreator::get_none_font()
{
	if (!none_font)
	{
		none_font = new NoneFont;
	}
	return *none_font;
}

Font& ResourceCreator::get_font(const SIZE& s, const string& f)
{
	Font *font = NULL;
	for (size_t i=0; i<fonts.size(); ++i)
	{
		font = fonts[i];
		if (font && font->equal(s, f))
		{
			return *font;
		}
	}
	if (!font)
	{
		font = new WinFont(s, f);
	}
	fonts.push_back(font);
	return *font;
}
