#pragma once
#include "CreationObserver.h"
#include "Shape.h"
#include <vector>
#include "BaseCreator.h"

namespace paint
{
	class Renderer : public CreationObserver
	{
	public:
		Renderer(HWND hWnd);

		void NotifyCreationFinished() override;
		void NotifyCreationStateChanged() override;

		void Render();

		void SetActiveCreator(std::shared_ptr<ICreator> creator) { m_currentCreator = creator; }
		std::shared_ptr<ICreator> GetActiveCreator() { return m_currentCreator; }

	private:
		void RenderShape(HDC hdc, Shape* shape);

		void Init();

		HWND m_hwnd;
		HBITMAP m_offscreenBitmap;
		HDC m_offscreenHdc;
		RECT m_wndClientRect;
		LPPAINTSTRUCT m_ps;
		HDC m_screenContext;

		std::shared_ptr<ICreator> m_currentCreator;
		std::vector<Shape*> m_shapes;
	};
}