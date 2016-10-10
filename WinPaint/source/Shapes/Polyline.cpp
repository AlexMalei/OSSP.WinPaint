#include "stdafx.h"
#include "Polyline.h"

using namespace paint;

/////////////////////////////////////////////////////

Polyline::Polyline()
{

}

/////////////////////////////////////////////////////

void Polyline::AddSegment(int x1, int y1, int x2, int y2)
{
	m_segments.push_back(Line(x1, y1, x2, y2));
}

/////////////////////////////////////////////////////

void Polyline::AddSegment(Point from, Point to)
{
	m_segments.push_back(Line(from, to));
}

/////////////////////////////////////////////////////

void Polyline::Serialize(std::ostream& s)
{

}

/////////////////////////////////////////////////////

void Polyline::Deserialize(std::istream& s)
{

}

/////////////////////////////////////////////////////

tinyxml2::XMLElement* Polyline::ToXml(tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* element = doc->NewElement("Pen");

	for (auto& line : m_segments)
	{
		element->InsertEndChild(line.ToXml(doc));
	}

	return element;
}

/////////////////////////////////////////////////////

void Polyline::FromXml(tinyxml2::XMLElement* element)
{
	for (auto lineNode = element->FirstChild(); lineNode; lineNode = lineNode->NextSibling())
	{
		Line segment;
		segment.FromXml(lineNode->ToElement());
		m_segments.push_back(segment);
	}
}

/////////////////////////////////////////////////////
