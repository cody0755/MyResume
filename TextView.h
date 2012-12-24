#pragma once
#include "view.h"
#include "Font.h"

class TextView : public View
{
public:
	TextView(View *parent = NULL);
	virtual ~TextView(void);

	virtual void draw(Painter &painter);
	virtual void parse_self(const PropMap&);

	void set_text(const string&);
	const string& get_text() const;
	void set_font(const Font&);
	Font& get_font();
	const Font& get_font() const;
	void set_text_clr(unsigned long, COLORREF);
	const StatusColorMap& get_text_clr() const;
	bool get_text_clr(unsigned long, COLORREF&) const;
private:
	int get_text_count() const;
	SIZE get_text_size() const;
	POINT get_text_origin() const;
private:
	string text;
	Font *font;
	StatusColorMap text_clrs;
};
