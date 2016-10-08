#pragma once
#include "Line.h"
#include "Point.h"
#include <vector>

namespace paint
{
	class Pen : public Shape
	{
		friend class PenDrawer;

	public:
		Pen();

		virtual Tool GetTool() override { return Tool::Pen; }

		const std::vector<Line>& GetLines() { return m_lines; }

		void AddSegment(int x1, int y1, int x2, int y2);
		void AddSegment(Point from, Point to);
		void AddSegment(Line segment) { m_lines.push_back(segment); }

	protected:
		std::vector<Line> m_lines;
	};
}
