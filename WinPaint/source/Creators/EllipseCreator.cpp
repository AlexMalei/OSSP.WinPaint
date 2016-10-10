#include "stdafx.h"
#include "EllipseCreator.h"
#include "Shapes/Ellipse.h"

using namespace paint;

/////////////////////////////////////////////////////

void EllipseCreator::OnPress(int x, int y)
{
	Point startPoint(x, y);
	m_createdShape = new Ellipse(startPoint, startPoint);
}

/////////////////////////////////////////////////////

void EllipseCreator::OnRelease(int x, int y)
{
	if (m_createdShape)
	{
		static_cast<Ellipse*>(m_createdShape)->SetBottomRight(Point(x, y));

		NotifyAll(&CreationObserver::NotifyCreationFinished);
		m_createdShape = nullptr;
	}
}

/////////////////////////////////////////////////////

void EllipseCreator::OnMove(int x, int y)
{
	if (m_createdShape)
	{
		static_cast<Ellipse*>(m_createdShape)->SetBottomRight(Point(x, y));
		NotifyAll(&CreationObserver::NotifyCreationStateChanged);
	}
}

/////////////////////////////////////////////////////

void EllipseCreator::Update()
{

}

/////////////////////////////////////////////////////

void EllipseCreator::OnKeyPress(DWORD keyCode)
{

}

/////////////////////////////////////////////////////
