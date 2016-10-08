#pragma once
#include "Line.h"
#include "Point.h"

namespace paint
{
	class Rectangle : public Line
	{
	public:
		Rectangle();
		Rectangle(int x, int y, int width, int height);
		Rectangle(Point topLeft, Point rightBottom);

		int GetWidth() { return abs(m_rightBottom.x - m_topLeft.x); }
		int GetHeight() { return abs(m_rightBottom.y - m_topLeft.y); }

		virtual Tool GetTool() override { return Tool::Rectangle; }
	};
}
