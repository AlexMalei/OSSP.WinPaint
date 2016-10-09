#pragma once
#include "stdafx.h"
#include "RectangleRenderer.h"
#include "Shapes/Rectangle.h"
#include "AppContext.h"

using namespace paint;

/////////////////////////////////////////////////////

void RectangleRenderer::Render(Shape* shape)
{
	Rectangle* rect = static_cast<Rectangle*>(shape);

	auto topLeft = rect->GetTopLeft();
	auto bottomRight = rect->GetRightBottom();

	AppContext::GetInstance()->GetRenderer()->DrawRect(topLeft, bottomRight);
}

/////////////////////////////////////////////////////
