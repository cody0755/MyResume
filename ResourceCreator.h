#ifndef MYRESUME_RESOURCECREATOR_H
#define MYRESUME_RESOURCECREATOR_H
#include "Font.h"

class ResourceCreator
{
private:
	ResourceCreator(void);
	~ResourceCreator(void);
public:
	static ResourceCreator& instance();
	NoneFont& get_none_font();
	Font& get_font(const SIZE& s, const string& f);

private:
	NoneFont *none_font;
	vector<Font*> fonts;
};

#endif
