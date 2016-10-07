#pragma once

namespace paint
{
	enum class ShapeType
	{
		Line,
		Rectangle,
		Ellipse,
		Circle,
		Polyline
	};

	class Shape
	{
	public:
		virtual ~Shape() {}

		virtual ShapeType GetType() = 0;
	};
}
