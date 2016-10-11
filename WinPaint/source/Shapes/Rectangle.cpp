#include "stdafx.h"
#include "Rectangle.h"

using namespace paint;

/////////////////////////////////////////////////////

Rectangle::Rectangle()
{}

/////////////////////////////////////////////////////

Rectangle::Rectangle(int x, int y, int width, int height)
	: Line(Point(x, y), Point(x + width, y + height))
{}

/////////////////////////////////////////////////////

Rectangle::Rectangle(Point topLeft, Point rightBottom)
	: Line(topLeft, rightBottom)
{}

/////////////////////////////////////////////////////

tinyxml2::XMLElement* Rectangle::ToXml(tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* element = doc->NewElement("Rectangle");
	element->InsertEndChild(m_topLeft.ToXml(doc));
	element->InsertEndChild(m_rightBottom.ToXml(doc));
	element->InsertEndChild(m_style.ToXml(doc));

	return element;
}

/////////////////////////////////////////////////////

void Rectangle::FromXml(tinyxml2::XMLElement* element)
{
	auto fromElement = element->FirstChild();
	auto toElement = fromElement->NextSibling();
	auto styleElement = toElement->NextSibling();

	m_topLeft.FromXml(fromElement->ToElement());
	m_rightBottom.FromXml(toElement->ToElement());
	m_style.FromXml(styleElement->ToElement());
}

/////////////////////////////////////////////////////