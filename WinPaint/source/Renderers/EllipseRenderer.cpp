#pragma once
#include "stdafx.h"
#include "EllipseRenderer.h"
#include "Shapes/Ellipse.h"
#include "AppContext.h"

using namespace paint;

/////////////////////////////////////////////////////

void EllipseRenderer::Render(Shape* shape)
{
	Ellipse* ellipse = static_cast<Ellipse*>(shape);

	auto topLeft = ellipse->GetTopLeft();
	auto bottomRight = ellipse->GetRightBottom();

	AppContext::GetInstance()->GetRenderer()->DrawEllipse(topLeft, bottomRight);
}

/////////////////////////////////////////////////////
