#pragma once
#include "Line.h"
#include "Point.h"

namespace paint
{
	class Ellipse : public Line
	{
	public:
		Ellipse();
		Ellipse(int x, int y, int radius, int subradius);
		Ellipse(Point topLeft, Point rightBottom);

		int GetWidth() { return abs(m_rightBottom.x - m_topLeft.x); }
		int GetHeight() { return abs(m_rightBottom.y - m_topLeft.y); }

		virtual Tool GetTool() override { return Tool::Ellipse; }

		virtual tinyxml2::XMLElement* ToXml(tinyxml2::XMLDocument* doc) override;
		virtual void FromXml(tinyxml2::XMLElement* element) override;
	};
}
