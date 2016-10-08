#include "stdafx.h"
#include "PenDrawer.h"
#include "Shapes/Pen.h"

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
		/*static_cast<Line*>(m_createdShape)->SetBottomRight(Point(x, y));

		NotifyAll(&CreationObserver::NotifyCreationFinished);
		m_createdShape = nullptr;*/
	}
}

/////////////////////////////////////////////////////

void PenDrawer::OnMove(int x, int y)
{
	if (m_createdShape)
	{
		/*static_cast<Line*>(m_createdShape)->SetBottomRight(Point(x, y));
		NotifyAll(&CreationObserver::NotifyCreationStateChanged);*/
	}
}

/////////////////////////////////////////////////////

void PenDrawer::OnDoubleClick(int x, int y)
{

}

/////////////////////////////////////////////////////
