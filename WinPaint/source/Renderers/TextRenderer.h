#pragma once
#include "IRenderer.h"

namespace paint
{
	class Shape;

	class TextRenderer : public IRenderer
	{
	public:
		virtual void Render(Shape* shape) override;
	};
}
