#pragma once
#include "stdafx.h"
#include "System/Singleton.h"
#include "Renderer.h"
#include "Creators/BaseCreator.h"

namespace paint
{
	class AppContext : public Singleton<AppContext>
	{
	public:
		AppContext(HWND hWnd);
		~AppContext();

		void InitInputManager();

		void Cleanup();

		void OnRender();
		void OnResize(Point size);

		ICreator* GetCurrentCreator() { return m_currentCreator.get(); }

	private:
		HWND m_hwnd;
		std::unique_ptr<Renderer> m_renderer;
		std::shared_ptr<ICreator> m_currentCreator;
	};
}
