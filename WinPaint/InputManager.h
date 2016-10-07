#pragma once
#include "System/Singleton.h"
#include "System/SafeEnum.h"

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

	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager();

		void Update();

	private:
		bool m_mousePressed[MouseButton::Count];
	};
}
