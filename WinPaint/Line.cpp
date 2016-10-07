#include "stdafx.h"
#include "Line.h"

using namespace paint;

/////////////////////////////////////////////////////

Line::Line()
{}

/////////////////////////////////////////////////////

Line::Line(int x, int y, int x2, int y2)
	: m_topLeft(Point(x, y))
	, m_rightBottom(Point(x2, y2))
{}

/////////////////////////////////////////////////////

Line::Line(Point topLeft, Point rightBottom)
	: m_topLeft(topLeft)
	, m_rightBottom(rightBottom)
{}

/////////////////////////////////////////////////////