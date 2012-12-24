#include "StdAfx.h"
#include "XmlParser.h"
#include "tinyxml/tinyxml.h"
#include "ResourceCreator.h"
#include "View.h"

XmlParser::XmlParser(void)
{}

XmlParser::~XmlParser(void)
{}

View* XmlParser::parse(const string& xml)
{
	TiXmlDocument doc(xml);
	if (!doc.LoadFile())
	{
		return NULL;
	}
	TiXmlElement *re = doc.RootElement();
	if (!re)
	{
		return NULL;
	}
	return parse_element(re);
}

View* XmlParser::parse_element(TiXmlElement *e, View *parent /* = NULL */)
{
	if (!e)
	{
		return NULL;
	}
	View *view = ResourceCreator::instance().get_view(e->Value());
	if (!view)
	{
		return NULL;
	}
	if (parent)
	{
		view->set_parent(parent);
		parent->push_child(view);
	}
	TiXmlAttribute *a = e->FirstAttribute();
	PropMap props;
	while(a)
	{
		props.insert(make_pair(a->Name(), a->Value()));
		a = a->Next();
	}
	view->parse(props);

	TiXmlNode *node = e->FirstChild();
	if (!node)
	{
		return view;
	}
	TiXmlElement *sub = node->ToElement();
	while (sub)
	{
		View* sv = parse_element(sub, view);
		sub = sub->NextSiblingElement();
	}
	return view;
}