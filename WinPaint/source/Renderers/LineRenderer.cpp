#pragma once
#include "stdafx.h"
#include "LineRenderer.h"
#include "Shapes/Line.h"
#include "AppContext.h"

using namespace paint;

/////////////////////////////////////////////////////

void LineRenderer::Render(Shape* shape)
{
	Line* line = static_cast<Line*>(shape);

	auto topLeft = line->GetTopLeft();
	auto bottomRight = line->GetRightBottom();

	AppContext::GetInstance()->GetRenderer()->DrawLine(topLeft, bottomRight);
}

/////////////////////////////////////////////////////
