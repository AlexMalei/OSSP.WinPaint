#pragma once
#include "stdafx.h"
#include "System/Singleton.h"
#include "Renderer.h"
#include "Toolbar.h"

namespace paint
{
	class AppContext : public Singleton<AppContext>
	{
	public:
		AppContext(HWND hWnd);
		~AppContext();

		void InitInputManager();
		void InitToolbar();

		void Cleanup();

		void OnRender();
		void OnResize(Point size);

		ICreator* GetCurrentTool() const  { return m_toolbar->GetCurrentTool(); }
		Toolbar* GetToolbar() const { return m_toolbar.get(); }
		Renderer* GetRenderer() const { return m_renderer.get(); }
		HWND GetWindowHandle() const { return m_hwnd; }

	private:
		HWND m_hwnd;
		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<Toolbar> m_toolbar;
	};
}
