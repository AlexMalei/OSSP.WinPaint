#pragma once

namespace paint
{
	class Shape;

	class IRenderer
	{
	public:
		virtual void Render(Shape* shape) = 0;
	};
}
