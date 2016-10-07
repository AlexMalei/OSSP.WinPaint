#include "stdafx.h"
#include "InputManager.h"

using namespace paint;

/////////////////////////////////////////////////////

InputManager::InputManager()
{

}

/////////////////////////////////////////////////////

void InputManager::Update(HWND hwnd)
{
	RefreshCursorPosition(hwnd);

	bool mousePressedOld[MouseButton::Count];

	for (WORD i = 0; i < MouseButton::Count; i++)
	{
		mousePressedOld[i] = m_mousePressed[i];
	}

	ParseKeyState(VK_LBUTTON, m_mouseToogled[0], m_mousePressed[0]);
	ParseKeyState(VK_RBUTTON, m_mouseToogled[1], m_mousePressed[1]);
	ParseKeyState(VK_MBUTTON, m_mouseToogled[2], m_mousePressed[2]);

	for (WORD i = 0; i < MouseButton::Count; i++)
	{
		if (m_mousePressed[i] != mousePressedOld[i])
		{
			if (m_mousePressed[i])
			{
				EmitMousePressEvent(static_cast<MouseButton>(i));
			}
			else
			{
				EmitMouseReleaseEvent(static_cast<MouseButton>(i));
			}
		}
	}
}

/////////////////////////////////////////////////////

void InputManager::ParseKeyState(int virtualKey, bool& lowBit, bool& highBit)
{
	SHORT state = GetKeyState(virtualKey);
	lowBit = state & 1;
	highBit = !!(static_cast<WORD>(state) >> 15);
}

/////////////////////////////////////////////////////

void InputManager::EmitMousePressEvent(MouseButton button)
{
	for (auto callback : m_mousePressCallbacks)
	{
		if (callback)
		{
			callback(button, m_mousePosition);
		}
	}
}

/////////////////////////////////////////////////////

void InputManager::EmitMouseReleaseEvent(MouseButton button)
{
	for (auto callback : m_mouseReleaseCallbacks)
	{
		if (callback)
		{
			callback(button, m_mousePosition);
		}
	}
}

/////////////////////////////////////////////////////

void InputManager::EmitMouseMoveEvent()
{
	for (auto callback : m_mouseMoveCallbacks)
	{
		if (callback)
		{
			callback(m_mousePosition);
		}
	}
}

/////////////////////////////////////////////////////

void InputManager::AddMousePressCallback(mousePressCallback callback)
{
	AddCallback(m_mousePressCallbacks, callback);
}

/////////////////////////////////////////////////////

void InputManager::AddMouseReleaseCallback(mouseReleaseCallback callback)
{
	AddCallback(m_mouseReleaseCallbacks, callback);
}

/////////////////////////////////////////////////////

void InputManager::AddMouseMoveCallback(mouseMoveCallback callback)
{
	AddCallback(m_mouseMoveCallbacks, callback);
}

/////////////////////////////////////////////////////

void InputManager::RefreshCursorPosition(HWND hwnd)
{
	Point mousePositionOld = m_mousePosition;
	POINT cursorPosition;
	GetCursorPos(&cursorPosition);
	ScreenToClient(hwnd, &cursorPosition);
	m_mousePosition = Point(cursorPosition.x, cursorPosition.y);

	if ((m_mousePosition.x != mousePositionOld.x) || (m_mousePosition.y != mousePositionOld.y))
	{
		EmitMouseMoveEvent();
	}
}

/////////////////////////////////////////////////////
