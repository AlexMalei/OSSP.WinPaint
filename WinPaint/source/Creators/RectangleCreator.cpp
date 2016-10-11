#include "stdafx.h"
#include "RectangleCreator.h"
#include "Shapes/Rectangle.h"

using namespace paint;

/////////////////////////////////////////////////////

void RectangleCreator::OnPress(int x, int y)
{
	Point startPoint(x, y);
	m_createdShape = new Rectangle(startPoint, startPoint);
}

/////////////////////////////////////////////////////

void RectangleCreator::OnRelease(int x, int y)
{
	if (m_createdShape)
	{
		static_cast<Rectangle*>(m_createdShape)->SetBottomRight(Point(x, y));

		NotifyAll(&CreationObserver::NotifyCreationFinished);
		m_createdShape = nullptr;
	}
}

/////////////////////////////////////////////////////

void RectangleCreator::OnMove(int x, int y)
{
	if (m_createdShape)
	{
		static_cast<Rectangle*>(m_createdShape)->SetBottomRight(Point(x, y));
		NotifyAll(&CreationObserver::NotifyCreationStateChanged);
	}
}

/////////////////////////////////////////////////////

void RectangleCreator::OnKeyPress(DWORD keyCode)
{

}

/////////////////////////////////////////////////////
