#include "stdafx.h"
#include "LineCreator.h"
#include "Shapes/Line.h"
#include "AppContext.h"

using namespace paint;

/////////////////////////////////////////////////////

void LineCreator::OnPress(int x, int y)
{
	Point startPoint(x, y);
	m_createdShape = new Line(startPoint, startPoint);

	auto toolbar = AppContext::GetInstance()->GetToolbar();
	m_createdShape->SetPenColor(toolbar->GetPenColor());
	m_createdShape->SetLineThickness(toolbar->GetLineThickness());
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

void LineCreator::OnKeyPress(DWORD keyCode)
{

}

/////////////////////////////////////////////////////
