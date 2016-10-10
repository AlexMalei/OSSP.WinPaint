#pragma once
#include "stdafx.h"
#include "PolylineRenderer.h"
#include "Shapes/Polyline.h"
#include "AppContext.h"

using namespace paint;

/////////////////////////////////////////////////////

void PolylineRenderer::Render(Shape* shape)
{
	Polyline* polyline = static_cast<Polyline*>(shape);

	auto segments = polyline->GetSegments();
	for (auto& segment : segments)
	{
		auto from = segment.GetTopLeft();
		auto to = segment.GetRightBottom();

		AppContext::GetInstance()->GetRenderer()->DrawLine(from, to);
	}
}

/////////////////////////////////////////////////////
