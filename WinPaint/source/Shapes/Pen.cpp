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
	m_lines.push_back(Line(x1, y1, x2, y2));
}

/////////////////////////////////////////////////////

void Pen::AddSegment(Point from, Point to)
{
	m_lines.push_back(Line(from, to));
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

	return element;
}

/////////////////////////////////////////////////////

void Pen::FromXml(tinyxml2::XMLElement* element)
{
	for (auto lineNode = element->FirstChild(); lineNode; lineNode = lineNode->NextSibling())
	{
		Line segment;
		segment.FromXml(lineNode->ToElement());
		m_lines.push_back(segment);
	}
}

/////////////////////////////////////////////////////
