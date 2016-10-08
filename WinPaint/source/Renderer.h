#pragma once
#include "Observers/CreationObserver.h"
#include "Shapes/Shape.h"
#include <vector>
#include "Creators/BaseCreator.h"
#include "Shapes/Point.h"

namespace paint
{
	class Renderer
	{
	public:
		Renderer(HWND hWnd);

		void Init();

		void Render();

		void Resize(Point size);

		void Refresh();

		BITMAP GetImage();

	private:
		void RenderShape(Shape* shape);
		
		void InitBackbuffer(HDC context, int width, int height);

		HWND m_hwnd; // Window handle
		HBITMAP m_offscreenBitmap;	// Offscreen buffer
		HDC m_offscreenHdc;			// Backbuffer context
		RECT m_wndClientRect;		// Client rect
		HDC m_screenContext;

		std::vector<Shape*> m_shapes;
	};
}