#include "stdafx.h"
#include "Text.h"
#include "TinyXml/tinyxml2.h"

using namespace paint;
using namespace tinyxml2;

/////////////////////////////////////////////////////

Text::Text()
{}

/////////////////////////////////////////////////////

Text::Text(int x, int y)
	: m_topLeft(Point(x, y))
{}

/////////////////////////////////////////////////////

Text::Text(Point topLeft)
	: m_topLeft(topLeft)
{}

/////////////////////////////////////////////////////

Text::Text(int x, int y, const std::string& text)
	: m_topLeft(Point(x, y))
	, m_text(text)
{}

/////////////////////////////////////////////////////

Text::Text(Point topLeft, const std::string& text)
	: m_topLeft(topLeft)
	, m_text(text)
{}

/////////////////////////////////////////////////////

void Text::EraseLast()
{
	if (m_text.length() > 0)
	{
		m_text.pop_back();
	}
}

/////////////////////////////////////////////////////

void Text::Serialize(std::ostream& s)
{
	
}

/////////////////////////////////////////////////////

void Text::Deserialize(std::istream& s)
{
	
}

/////////////////////////////////////////////////////

tinyxml2::XMLElement* Text::ToXml(tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* element = doc->NewElement("Text");
	
	element->InsertEndChild(m_topLeft.ToXml(doc));								// Position
	tinyxml2::XMLElement* textElement = doc->NewElement("Value");				// Text value
	textElement->SetText(m_text.c_str());										//
	element->InsertEndChild(textElement);										//
	tinyxml2::XMLElement* colorElement = doc->NewElement("Color");				// Color
	colorElement->SetAttribute("Value", static_cast<unsigned int>(m_color));	//
	element->InsertEndChild(colorElement);										//
	element->InsertEndChild(m_font->ToXml(doc));								// Font
	
	return element;
}

/////////////////////////////////////////////////////

void Text::FromXml(tinyxml2::XMLElement* element)
{
	auto topLeftElement = element->FirstChild();
	auto textElement = topLeftElement->NextSibling();
	auto colorElement = textElement->NextSibling();
	auto fontElement = colorElement->NextSibling();

	m_topLeft.FromXml(topLeftElement->ToElement());
	m_text = textElement->ToElement()->GetText();
	m_color = colorElement->ToElement()->UnsignedAttribute("Value");
	m_font = std::make_shared<Font>();
	m_font->FromXml(fontElement->ToElement());
}

/////////////////////////////////////////////////////
