#include "stdafx.h"
#include "PenDrawer.h"
#include "Shapes/Pen.h"
#include "Shapes/Line.h"

using namespace paint;

/////////////////////////////////////////////////////

void PenDrawer::OnPress(int x, int y)
{
	Point startPoint(x, y);
	m_createdShape = new Pen();
	static_cast<Pen*>(m_createdShape)->AddSegment(startPoint, startPoint);
}

/////////////////////////////////////////////////////

void PenDrawer::OnRelease(int x, int y)
{
	if (m_createdShape)
	{
		NotifyAll(&CreationObserver::NotifyCreationFinished);
		m_createdShape = nullptr;
	}
}

/////////////////////////////////////////////////////

void PenDrawer::OnMove(int x, int y)
{
	AddSegment(Point(x, y));
}

/////////////////////////////////////////////////////

void PenDrawer::AddSegment(Point currentPos)
{
	if (m_createdShape)
	{
		Pen* pen = static_cast<Pen*>(m_createdShape);
		Line& lastLine = pen->m_lines[pen->m_lines.size() - 1];
		Line segment = Line(lastLine.GetRightBottom(), currentPos);
		pen->AddSegment(segment);

		NotifyAll(&CreationObserver::NotifyCreationStateChanged);
	}
}

/////////////////////////////////////////////////////
