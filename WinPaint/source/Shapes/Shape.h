#pragma once
#include "ToolDefs.h"

namespace paint
{
	class Shape
	{
	public:
		virtual ~Shape() {}

		virtual Tool GetTool() = 0;
	};
}
