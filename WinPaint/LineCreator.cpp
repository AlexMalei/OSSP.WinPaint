#include "stdafx.h"
#include "LineCreator.h"
#include "Line.h"

using namespace paint;

/////////////////////////////////////////////////////

void LineCreator::OnPress(int x, int y)
{
	Point startPoint(x, y);
	m_createdShape = new Line(startPoint, startPoint);
}

/////////////////////////////////////////////////////

void LineCreator::OnRelease(int x, int y)
{
	if (m_createdShape)
	{
		static_cast<Line*>(m_createdShape)->SetBottomRight(Point(x, y));

		NotifyAll(&CreationObserver::NotifyCreationFinished);
		m_createdShape = nullptr;
	}
}

/////////////////////////////////////////////////////

void LineCreator::OnMove(int x, int y)
{
	if (m_createdShape)
	{
		static_cast<Line*>(m_createdShape)->SetBottomRight(Point(x, y));
		NotifyAll(&CreationObserver::NotifyCreationStateChanged);
	}
}

/////////////////////////////////////////////////////

void LineCreator::OnDoubleClick(int x, int y)
{

}

/////////////////////////////////////////////////////
