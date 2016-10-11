#include "stdafx.h"
#include "PolylineCreator.h"
#include "Shapes/Polyline.h"
#include "AppContext.h"

using namespace paint;

/////////////////////////////////////////////////////

void PolylineCreator::OnPress(int x, int y)
{
	Point startPoint(x, y);
	if (m_createdShape == nullptr)
	{
		m_createdShape = new Polyline();

		auto toolbar = AppContext::GetInstance()->GetToolbar();
		m_createdShape->SetPenColor(toolbar->GetPenColor());
		m_createdShape->SetLineThickness(toolbar->GetLineThickness());
	}

	static_cast<Polyline*>(m_createdShape)->AddSegment(startPoint, startPoint);
	NotifyAll(&CreationObserver::NotifyCreationStateChanged);
}

/////////////////////////////////////////////////////

void PolylineCreator::OnRelease(int x, int y)
{
	
}

/////////////////////////////////////////////////////

void PolylineCreator::OnMove(int x, int y)
{
	if (m_createdShape)
	{
		const auto& segments = static_cast<Polyline*>(m_createdShape)->GetSegments();
		Line& lastSegment = const_cast<Line&>(segments[segments.size() - 1]);

		lastSegment.SetBottomRight(Point(x, y));
		NotifyAll(&CreationObserver::NotifyCreationStateChanged);
	}
}

/////////////////////////////////////////////////////

void PolylineCreator::AddSegment(Point currentPos)
{
	if (m_createdShape)
	{
		Polyline* pen = static_cast<Polyline*>(m_createdShape);
		Line& lastLine = pen->m_segments[pen->m_segments.size() - 1];
		Line segment = Line(lastLine.GetRightBottom(), currentPos);
		pen->AddSegment(segment);
	}
}

/////////////////////////////////////////////////////

void PolylineCreator::OnKeyPress(DWORD keyCode)
{
	if (keyCode == VK_SPACE)
	{
		if (m_createdShape)
		{
			NotifyAll(&CreationObserver::NotifyCreationFinished);
			m_createdShape = nullptr;
		}
	}
}

/////////////////////////////////////////////////////
