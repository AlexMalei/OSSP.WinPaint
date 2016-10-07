#pragma once
#include "Shape.h"
#include "Point.h"

namespace paint
{
	class Line : public Shape
	{
	public:
		Line();
		Line(int x, int y, int x2, int y2);
		Line(Point topLeft, Point rightBottom);

		Point GetTopLeft() { return m_topLeft; }
		Point GetRightBottom() { return m_rightBottom; }
		void SetTopLeft(const Point& p) { m_topLeft = p; }
		void SetBottomRight(const Point& p) { m_rightBottom = p; }

		virtual ShapeType GetType() override { return ShapeType::Line; }

	protected:
		Point m_topLeft;
		Point m_rightBottom;
	};
}
