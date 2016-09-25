#include "stdafx.h"
#include "Rectangle.h"

using namespace paint;

Rectangle::Rectangle()
{}

Rectangle::Rectangle(int x, int y, int width, int height)
	: Line(Point(x, y), Point(x + width, y + height))
{}

Rectangle::Rectangle(Point topLeft, Point rightBottom)
	: Line(topLeft, rightBottom)
{}
