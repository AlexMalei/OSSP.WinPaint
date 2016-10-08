#pragma once
#include "IRenderer.h"

namespace paint
{
	class Shape;

	class PenRenderer : public IRenderer
	{
	public:
		virtual void Render(Shape* shape) override;
	};
}
