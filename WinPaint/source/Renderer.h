#pragma once
#include "Observers/CreationObserver.h"
#include "Shapes/Shape.h"
#include <vector>
#include "Creators/BaseCreator.h"
#include "Shapes/Point.h"
#include "Shapes/Font.h"
#include "Renderers/IRenderer.h"
#include <unordered_map>

namespace paint
{
	class Renderer
	{
	public:
		Renderer(HWND hWnd);

		void Init();
		void InitShapeRenderers();

		void Render();

		void Resize(Point size);
		void Refresh();

		BITMAP GetImage();
		Point GetSize();

		IRenderer* GetShapeRenderer(Tool tool) const;

		void DrawLine(Point from, Point to);
		void DrawRect(Point from, Point to, bool hollow);
		void DrawEllipse(Point from, Point to, bool hollow);
		void DrawText(Point position, LPCSTR text, DWORD length, Font* font, COLORREF color);

		HDC GetBackBuffer() const { return m_offscreenHdc; }
		HDC GetScreenBuffer() const { return m_screenContext; }

	private:
		void RenderShape(Shape* shape);
		void RefreshShapeStyle(Shape* shape);
		
		void InitBackbuffer(HDC context, int width, int height);

		HWND m_hwnd;				// Window handle
		HBITMAP m_offscreenBitmap;	// Offscreen buffer
		HDC m_offscreenHdc;			// Backbuffer context
		RECT m_wndClientRect;		// Client rect
		HDC m_screenContext;

		std::vector<Shape*> m_shapes;
		std::unordered_map<int, IRenderer*> m_shapeRenderers;
	};
}