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

		virtual Tool GetTool() override { return Tool::Line; }

		virtual void Serialize(std::ostream& s) override;
		virtual void Deserialize(std::istream& s) override;

		virtual tinyxml2::XMLElement* ToXml(tinyxml2::XMLDocument* doc) override;
		virtual void FromXml(tinyxml2::XMLElement* element) override;

	protected:
		Point m_topLeft;
		Point m_rightBottom;
	};
}
