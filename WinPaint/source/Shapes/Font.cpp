#include "stdafx.h"
#include "Font.h"

using namespace paint;

/////////////////////////////////////////////////////

Font::Font()
{

}

/////////////////////////////////////////////////////

Font::Font(LPLOGFONTA logicFont)
{
	m_face = logicFont->lfFaceName;
	m_sizeX = logicFont->lfWidth;
	m_sizeY = logicFont->lfHeight;
	m_underlined = logicFont->lfUnderline;
	m_italic = logicFont->lfItalic;
	m_weight = logicFont->lfWeight;

	m_font = CreateFontIndirectA(logicFont);
}

/////////////////////////////////////////////////////

bool Font::IsBold() const
{
	return (m_weight == FW_BOLD);
}

/////////////////////////////////////////////////////

bool Font::IsItalic() const
{
	return (m_italic == TRUE);
}

/////////////////////////////////////////////////////

bool Font::IsUnderlined() const
{
	return (m_underlined == TRUE);
}

/////////////////////////////////////////////////////

LPSTR Font::GetFace() const
{
	return m_face;
}

/////////////////////////////////////////////////////

DWORD Font::GetSize() const
{
	return m_sizeY;
}

/////////////////////////////////////////////////////

tinyxml2::XMLElement* Font::ToXml(tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* element = doc->NewElement("Font");
	element->SetAttribute("face", m_face);
	element->SetAttribute("weight", m_weight);
	element->SetAttribute("width", m_sizeX);
	element->SetAttribute("height", m_sizeY);
	element->SetAttribute("italic", m_italic);
	element->SetAttribute("underline", m_underlined);

	return element;
}

/////////////////////////////////////////////////////

void Font::FromXml(tinyxml2::XMLElement* element)
{
	m_face = const_cast<LPSTR>(element->Attribute("face"));
	m_sizeX = element->IntAttribute("width");
	m_sizeY = element->IntAttribute("height");
	m_weight = element->IntAttribute("weight");
	m_italic = element->UnsignedAttribute("italic");
	m_underlined = element->UnsignedAttribute("underline");

	// Construct logic font
	LOGFONTA logicFont;
	ZeroMemory(&logicFont, sizeof(LOGFONTA));
	logicFont.lfWidth = m_sizeX;
	logicFont.lfHeight = m_sizeY;
	logicFont.lfCharSet = ANSI_CHARSET;
	logicFont.lfOrientation = 0;
	logicFont.lfEscapement = 0;
	memcpy(logicFont.lfFaceName, m_face, strlen(m_face));
	logicFont.lfWeight = m_weight;
	logicFont.lfQuality = PROOF_QUALITY;
	logicFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logicFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logicFont.lfItalic = m_italic;
	logicFont.lfUnderline = m_underlined;
	logicFont.lfStrikeOut = FALSE;
	logicFont.lfPitchAndFamily = FF_DONTCARE;

	m_font = CreateFontIndirectA(&logicFont);
}

/////////////////////////////////////////////////////
