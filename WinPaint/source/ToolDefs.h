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
		};
	};
	typedef SafeEnum<ToolDef> Tool;
}
