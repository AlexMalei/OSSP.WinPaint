#pragma once
#include "System/SafeEnum.h"

namespace paint
{
	struct ToolDef
	{
		enum type
		{
			Pen,
			Line,
			Ellipse,
			Rectangle,
			Polyline,
			Polygon,
			Text,
			Eraser,
			None
		};

		static const char* name(type item)
		{
			switch (item)
			{
			case type::Pen:
				return "Pen";
			case type::Line:
				return "Line";
			case type::Ellipse:
				return "Ellipse";
			case type::Rectangle:
				return "Rectangle";
			case type::Polyline:
				return "Polyline";
			case type::Polygon:
				return "Polygon";
			case type::Text:
				return "Text";
			case type::Eraser:
				return "Eraser";
			}

			return "None";
		}
	};
	typedef SafeEnum<ToolDef> Tool;
}
