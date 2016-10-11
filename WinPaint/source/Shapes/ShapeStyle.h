#pragma once
#include "stdafx.h"
#include "System/IXmlConvertable.h"

namespace paint
{
	struct ShapeStyle : IXmlConvertable
	{
		COLORREF m_penColor = 0;
		COLORREF m_brushColor = 0;
		DWORD m_penThickness = 1;

		virtual tinyxml2::XMLElement* ToXml(tinyxml2::XMLDocument* doc) override
		{
			tinyxml2::XMLElement* element = doc->NewElement("Style");
			element->SetAttribute("PenColor", static_cast<unsigned int>(m_penColor));
			element->SetAttribute("BrushColor", static_cast<unsigned int>(m_brushColor));
			element->SetAttribute("PenThickness", static_cast<unsigned int>(m_penThickness));

			return element;
		}

		virtual void FromXml(tinyxml2::XMLElement* element) override
		{
			m_penColor = element->UnsignedAttribute("PenColor");
			m_brushColor = element->UnsignedAttribute("BrushColor");
			m_penThickness = element->UnsignedAttribute("PenThickness");
		}
	};
}
