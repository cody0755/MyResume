#ifndef MYRESUME_XMLPARSER_H
#define MYRESUME_XMLPARSER_H
#include <map>
#include <string>
using namespace std;

typedef map<string, string> PropMap;
class View;
class TiXmlElement;
class XmlParser
{
public:
	XmlParser(void);
	virtual ~XmlParser(void);

	virtual View* parse(const string& xml);

	View* parse_element(TiXmlElement *, View *parent = NULL);
};

#endif