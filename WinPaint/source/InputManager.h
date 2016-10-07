#pragma once
#include "System/Singleton.h"
#include "System/SafeEnum.h"
#include "Shapes/Point.h"
#include <vector>

namespace paint
{
	struct MouseButtonDef
	{
		enum type
		{
			Left = 0,
			Right = 1,
			Middle = 2,
			Wheel = 2,
			Count = 3,
		};
	};
	typedef SafeEnum<MouseButtonDef> MouseButton;

	typedef void (*mousePressCallback)(MouseButton button, Point pos);
	typedef void(*mouseReleaseCallback)(MouseButton button, Point pos);
	typedef void(*mouseMoveCallback)(Point pos);

	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager();

		void Update(HWND hwnd);

		bool MouseKeyPressed(MouseButton button) { return m_mousePressed[button.value()]; }

		void AddMousePressCallback(mousePressCallback callback);
		void AddMouseReleaseCallback(mouseReleaseCallback callback);
		void AddMouseMoveCallback(mouseMoveCallback callback);

	private:
		void ParseKeyState(int virtualKey, bool& lowBit, bool& highBit);

		void EmitMousePressEvent(MouseButton button);
		void EmitMouseReleaseEvent(MouseButton button);
		void EmitMouseMoveEvent();

		void RefreshCursorPosition(HWND hwnd);

		template <class T>
		void AddCallback(std::vector<T>& container, T callback)
		{
			auto it = std::find(container.begin(), container.end(), callback);
			if (it == container.end())
			{
				container.push_back(callback);
			}
		}

		bool m_mousePressed[MouseButton::Count] = { false, false, false };
		bool m_mouseToogled[MouseButton::Count] = { false, false, false };
		Point m_mousePosition = Point(0, 0);

		std::vector<mousePressCallback> m_mousePressCallbacks;
		std::vector<mouseReleaseCallback> m_mouseReleaseCallbacks;
		std::vector<mouseMoveCallback> m_mouseMoveCallbacks;
	};
}
