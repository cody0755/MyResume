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
	void set_text_clr(unsigned long, colorref);
	const StatusColorMap& get_text_clr() const;
	bool get_text_clr(unsigned long, colorref&) const;
private:
	vector<string> get_text_lines() const;
	int get_text_count(const string&) const;
	Size get_text_size(const string&) const;
	void draw_text(Painter&, const vector<string>&, colorref) const;
private:
	string text;
	Font *font;
	StatusColorMap text_clrs;
};
