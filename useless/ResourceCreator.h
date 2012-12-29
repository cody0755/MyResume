#ifndef USELESS_RESOURCECREATOR_H
#define USELESS_RESOURCECREATOR_H
#include "Font.h"
#include "Interpolator.h"

class View;
class ResourceCreator
{
private:
	ResourceCreator(void);
	~ResourceCreator(void);
public:
	static ResourceCreator& instance();
	NoneFont& get_none_font();
	Font& get_font(const Size& s, const string& f);
	Interpolator* get_linear_interpolator();
	Interpolator* get_accelerate_interpolator();
	Interpolator* get_decelerate_interpolator();
	Interpolator* get_cycle_interpolator();
	Interpolator* get_accelerate_decelerate_interpolator();
	View* get_view(const string& view);

private:
	NoneFont *none_font;
	vector<Font*> fonts;
	Interpolator *lin_interpolator;
	Interpolator *acc_interpolator;
	Interpolator *dec_interpolator;
	Interpolator *cyc_interpolator;
	Interpolator *acc_dec_interpolator;
};

#endif
