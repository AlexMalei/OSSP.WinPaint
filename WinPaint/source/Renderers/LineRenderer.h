#pragma once
#include "IRenderer.h"

namespace paint
{
	class Shape;

	class LineRenderer : public IRenderer
	{
	public:
		virtual void Render(Shape* shape) override;
	};
}
