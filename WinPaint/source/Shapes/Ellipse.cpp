#include "stdafx.h"
#include "Ellipse.h"

using namespace paint;

/////////////////////////////////////////////////////

Ellipse::Ellipse()
{}

/////////////////////////////////////////////////////

Ellipse::Ellipse(int x, int y, int width, int height)
	: Line(Point(x, y), Point(x + width, y + height))
{}

/////////////////////////////////////////////////////

Ellipse::Ellipse(Point topLeft, Point rightBottom)
	: Line(topLeft, rightBottom)
{}

/////////////////////////////////////////////////////

tinyxml2::XMLElement* Ellipse::ToXml(tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* element = doc->NewElement("Ellipse");
	element->InsertEndChild(m_topLeft.ToXml(doc));
	element->InsertEndChild(m_rightBottom.ToXml(doc));
	element->InsertEndChild(m_style.ToXml(doc));

	return element;
}

/////////////////////////////////////////////////////

void Ellipse::FromXml(tinyxml2::XMLElement* element)
{
	auto fromElement = element->FirstChild();
	auto toElement = fromElement->NextSibling();
	auto styleElement = toElement->NextSibling();

	m_topLeft.FromXml(fromElement->ToElement());
	m_rightBottom.FromXml(toElement->ToElement());
	m_style.FromXml(styleElement->ToElement());
}

/////////////////////////////////////////////////////