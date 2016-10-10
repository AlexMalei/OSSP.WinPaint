#pragma once
#include "IRenderer.h"

namespace paint
{
	class Shape;

	class PolylineRenderer : public IRenderer
	{
	public:
		virtual void Render(Shape* shape) override;
	};
}
