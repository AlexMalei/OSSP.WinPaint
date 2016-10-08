#pragma once
#include "stdafx.h"
#include "System/ISerializable.h"

namespace paint
{
	struct Point
	{
		int x, y;

		Point(int _x = 0, int _y = 0)
			: x(_x)
			, y(_y)
		{}

		tinyxml2::XMLElement* ToXml(tinyxml2::XMLDocument* doc)
		{
			tinyxml2::XMLElement* element = doc->NewElement("Point");
			element->SetAttribute("x", x);
			element->SetAttribute("y", y);

			return element;
		}

		void FromXml(tinyxml2::XMLElement* element)
		{
			x = element->IntAttribute("x");
			y = element->IntAttribute("y");
		}
	};
}
