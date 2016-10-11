#include "stdafx.h"
#include "Line.h"
#include "TinyXml/tinyxml2.h"

using namespace paint;
using namespace tinyxml2;

/////////////////////////////////////////////////////

Line::Line()
{}

/////////////////////////////////////////////////////

Line::Line(int x, int y, int x2, int y2)
	: m_topLeft(Point(x, y))
	, m_rightBottom(Point(x2, y2))
{}

/////////////////////////////////////////////////////

Line::Line(Point topLeft, Point rightBottom)
	: m_topLeft(topLeft)
	, m_rightBottom(rightBottom)
{}

/////////////////////////////////////////////////////

void Line::Serialize(std::ostream& s)
{
	Tool tool = GetTool();
	const char* name = tool.name();

	XMLDocument doc;

	XMLElement* root = doc.NewElement("Document");
	doc.InsertFirstChild(root);

	root->SetAttribute("x", m_topLeft.x);
	root->SetAttribute("y", m_topLeft.y);

	doc.SaveFile("test_file.xml");
}

/////////////////////////////////////////////////////

void Line::Deserialize(std::istream& s)
{
	Tool tool = GetTool();
	const char* name = tool.name();
}

/////////////////////////////////////////////////////

tinyxml2::XMLElement* Line::ToXml(tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* element = doc->NewElement("Line");
	element->InsertEndChild(m_topLeft.ToXml(doc));
	element->InsertEndChild(m_rightBottom.ToXml(doc));
	element->InsertEndChild(m_style.ToXml(doc));

	return element;
}

/////////////////////////////////////////////////////

void Line::FromXml(tinyxml2::XMLElement* element)
{
	auto fromElement = element->FirstChild();
	auto toElement = fromElement->NextSibling();
	auto styleElement = toElement->NextSibling();

	m_topLeft.FromXml(fromElement->ToElement());
	m_rightBottom.FromXml(toElement->ToElement());
	m_style.FromXml(styleElement->ToElement());
}

/////////////////////////////////////////////////////
