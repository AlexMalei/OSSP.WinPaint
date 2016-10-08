#pragma once
#include "stdafx.h"
#include "PenRenderer.h"
#include "Shapes/Pen.h"
#include "AppContext.h"

using namespace paint;

/////////////////////////////////////////////////////

void PenRenderer::Render(Shape* shape)
{
	Pen* pen = static_cast<Pen*>(shape);

	auto penLines = pen->GetLines();
	for (auto& line : penLines)
	{
		auto from = line.GetTopLeft();
		auto to = line.GetRightBottom();

		AppContext::GetInstance()->GetRenderer()->DrawLine(from, to);
	}
}

/////////////////////////////////////////////////////
