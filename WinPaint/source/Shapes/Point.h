#pragma once
#include "stdafx.h"
#include "System/IXmlConvertable.h"

namespace paint
{
	struct Point : public IXmlConvertable
	{
		int x, y;

		Point(int _x = 0, int _y = 0)
			: x(_x)
			, y(_y)
		{}

		virtual tinyxml2::XMLElement* ToXml(tinyxml2::XMLDocument* doc) override
		{
			tinyxml2::XMLElement* element = doc->NewElement("Point");
			element->SetAttribute("x", x);
			element->SetAttribute("y", y);

			return element;
		}

		virtual void FromXml(tinyxml2::XMLElement* element) override
		{
			x = element->IntAttribute("x");
			y = element->IntAttribute("y");
		}
	};
}
