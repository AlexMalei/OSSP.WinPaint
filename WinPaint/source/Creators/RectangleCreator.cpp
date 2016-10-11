#include "stdafx.h"
#include "RectangleCreator.h"
#include "Shapes/Rectangle.h"
#include "AppContext.h"

using namespace paint;

/////////////////////////////////////////////////////

void RectangleCreator::OnPress(int x, int y)
{
	Point startPoint(x, y);
	m_createdShape = new Rectangle(startPoint, startPoint);

	auto toolbar = AppContext::GetInstance()->GetToolbar();
	m_createdShape->SetPenColor(toolbar->GetPenColor());
	m_createdShape->SetBrushColor(toolbar->GetBrushColor());
	m_createdShape->SetLineThickness(toolbar->GetLineThickness());
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
