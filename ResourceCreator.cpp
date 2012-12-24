#include "StdAfx.h"
#include "ResourceCreator.h"
#include "View.h"
#include "ButtonView.h"
#include "TextView.h"

ResourceCreator::ResourceCreator(void)
: none_font(NULL)
, lin_interpolator(NULL)
, acc_interpolator(NULL)
, dec_interpolator(NULL)
, cyc_interpolator(NULL)
, acc_dec_interpolator(NULL)
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
	font = new WinFont(s, f);
	if (!font)
	{
		return get_none_font();
	}
	if (!font->valid())
	{
		delete font;
		return get_none_font();
	}
	fonts.push_back(font);
	return *font;
}

Interpolator* ResourceCreator::get_linear_interpolator()
{
	if (!lin_interpolator)
	{
		lin_interpolator = new LinearInterpolator;
	}
	return lin_interpolator;
}

Interpolator* ResourceCreator::get_accelerate_interpolator()
{
	if (!acc_interpolator)
	{
		acc_interpolator = new AccelerateInterpolator;
	}
	return acc_interpolator;
}

Interpolator* ResourceCreator::get_decelerate_interpolator()
{
	if (!dec_interpolator)
	{
		dec_interpolator = new DecelerateInterpolator;
	}
	return dec_interpolator;
}

Interpolator* ResourceCreator::get_cycle_interpolator()
{
	if (!cyc_interpolator)
	{
		cyc_interpolator = new CycleInterpolator;
	}
	return cyc_interpolator;
}

Interpolator* ResourceCreator::get_accelerate_decelerate_interpolator()
{
	if (!acc_dec_interpolator)
	{
		acc_dec_interpolator = new AccelerateDecelerateInterpolator;
	}
	return acc_dec_interpolator;
}

View* ResourceCreator::get_view(const string& view)
{
	if ("view" == view)
	{
		return new View;
	}
	else if ("button" == view)
	{
		return new ButtonView;
	} 
	else if ("text" == view)
	{
		return new TextView;
	}
	return NULL;
}
