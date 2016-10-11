#include "stdafx.h"
#include "Pen.h"

using namespace paint;

/////////////////////////////////////////////////////

Pen::Pen()
{

}

/////////////////////////////////////////////////////

void Pen::AddSegment(int x1, int y1, int x2, int y2)
{
	AddSegment(Point(x1, y1), Point(x2, y2));
}

/////////////////////////////////////////////////////

void Pen::AddSegment(Point from, Point to)
{
	Line line = Line(from, to);
	line.SetStyle(m_style);
	m_lines.push_back(line);
}

/////////////////////////////////////////////////////

void Pen::Serialize(std::ostream& s)
{

}

/////////////////////////////////////////////////////

void Pen::Deserialize(std::istream& s)
{

}

/////////////////////////////////////////////////////

tinyxml2::XMLElement* Pen::ToXml(tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* element = doc->NewElement("Pen");

	for (auto& line : m_lines)
	{
		element->InsertEndChild(line.ToXml(doc));
	}

	element->InsertEndChild(m_style.ToXml(doc));

	return element;
}

/////////////////////////////////////////////////////

void Pen::FromXml(tinyxml2::XMLElement* element)
{
	tinyxml2::XMLNode* last = element->FirstChild();

	for (; last && (strcmp(last->Value(), "Line") == 0); last = last->NextSibling())
	{
		Line segment;
		segment.FromXml(last->ToElement());
		m_lines.push_back(segment);
	}

	m_style.FromXml(last->ToElement());
}

/////////////////////////////////////////////////////
