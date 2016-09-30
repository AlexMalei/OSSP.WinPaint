#pragma once
#include "CreationObserver.h"
#include "Shape.h"
#include <vector>
#include "BaseCreator.h"
#include "Point.h"

namespace paint
{
	class Renderer : public CreationObserver
	{
	public:
		Renderer(HWND hWnd);

		void Init();

		void NotifyCreationFinished() override;
		void NotifyCreationStateChanged() override;

		void Render();

		void SetActiveCreator(std::shared_ptr<ICreator> creator) { m_currentCreator = creator; }
		std::shared_ptr<ICreator> GetActiveCreator() { return m_currentCreator; }

		void Resize(Point size);

	private:
		void RenderShape(Shape* shape);
		
		void InitBackbuffer(HDC context, int width, int height);

		HWND m_hwnd; // Window handle
		HBITMAP m_offscreenBitmap;	// Offscreen buffer
		HDC m_offscreenHdc;			// Backbuffer context
		RECT m_wndClientRect;		// Client rect
		HDC m_screenContext;

		std::shared_ptr<ICreator> m_currentCreator;
		std::vector<Shape*> m_shapes;
	};
}