#include "stdafx.h"
#include "TextCreator.h"
#include "Shapes/Text.h"
#include "AppContext.h"

using namespace paint;

/////////////////////////////////////////////////////

void TextCreator::OnPress(int x, int y)
{
	Point startPoint(x, y);
	m_createdShape = new Text(startPoint);
	Text* text = static_cast<Text*>(m_createdShape);

	auto toolbar = AppContext::GetInstance()->GetToolbar();
	text->SetFont(toolbar->GetFont());
	text->SetColor(toolbar->GetPenColor());
}

/////////////////////////////////////////////////////

void TextCreator::OnRelease(int x, int y)
{
	
}

/////////////////////////////////////////////////////

void TextCreator::OnMove(int x, int y)
{
	
}

/////////////////////////////////////////////////////

void TextCreator::OnKeyPress(DWORD keyCode)
{
	if (m_createdShape)
	{
		if (keyCode == VK_RETURN)
		{
			NotifyAll(&CreationObserver::NotifyCreationFinished);
			m_createdShape = nullptr;
		}
		else if (keyCode == VK_BACK)
		{
			static_cast<Text*>(m_createdShape)->EraseLast();
			NotifyAll(&CreationObserver::NotifyCreationFinished);
		}
		else
		{
			char charCode = static_cast<char>(keyCode);
			if (charCode >= 32)
			{
				static_cast<Text*>(m_createdShape)->Append(charCode);
				NotifyAll(&CreationObserver::NotifyCreationStateChanged);
			}
		}
	}
}

/////////////////////////////////////////////////////
