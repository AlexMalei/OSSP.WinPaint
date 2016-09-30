#include "stdafx.h"
#include "Renderer.h"
#include "Line.h"

using namespace paint;

/////////////////////////////////////////////////////

Renderer::Renderer(HWND hWnd)
	: m_hwnd(hWnd)
{
	Init();

	auto shape = new paint::Line(paint::Point(25, 50), paint::Point(150, 75));
	m_shapes.push_back(shape);
}

/////////////////////////////////////////////////////

void Renderer::NotifyCreationFinished()
{
	m_shapes.push_back(m_currentCreator->GetShape());

	InvalidateRect(m_hwnd, nullptr, TRUE);
}

/////////////////////////////////////////////////////

void Renderer::NotifyCreationStateChanged()
{
	InvalidateRect(m_hwnd, nullptr, TRUE);
}

/////////////////////////////////////////////////////

void Renderer::Render()
{
	PAINTSTRUCT ps;
	m_screenContext = BeginPaint(m_hwnd, &ps);

	HBITMAP oldBitmap = static_cast<HBITMAP>(SelectObject(m_offscreenHdc, m_offscreenBitmap));

	// Fill backbuffer with system color
	HBRUSH hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	FillRect(m_offscreenHdc, &m_wndClientRect, hbrBkGnd);
	DeleteObject(hbrBkGnd);

	// Render the scene

	for (auto shape : m_shapes)
	{
		RenderShape(shape);
	}

	auto currentCreatorShape = m_currentCreator->GetShape();
	if (currentCreatorShape)
	{
		RenderShape(currentCreatorShape);
	}

	// 

	int width = m_wndClientRect.right - m_wndClientRect.left;
	int height = m_wndClientRect.bottom - m_wndClientRect.top;

	// Swap buffers
	BitBlt(m_screenContext, m_wndClientRect.left, m_wndClientRect.top, width, height, m_offscreenHdc, 0, 0, SRCCOPY);
	SelectObject(m_offscreenHdc, oldBitmap);

	EndPaint(m_hwnd, &ps);
}

/////////////////////////////////////////////////////

void Renderer::RenderShape(Shape* shape)
{
	auto shapeType = shape->GetType();

	switch (shapeType)
	{
	case paint::ShapeType::Line:
		paint::Line* line = static_cast<paint::Line*>(shape);

		auto topLeft = line->GetTopLeft();
		auto bottomRight = line->GetRightBottom();

		MoveToEx(m_offscreenHdc, topLeft.x, topLeft.y, NULL);
		LineTo(m_offscreenHdc, bottomRight.x, bottomRight.y);

		break;
	}
}

/////////////////////////////////////////////////////

void Renderer::Init()
{
	PAINTSTRUCT ps;
	m_screenContext = BeginPaint(m_hwnd, &ps);

	GetClientRect(m_hwnd, &m_wndClientRect);
	int width = m_wndClientRect.right - m_wndClientRect.left;
	int height = m_wndClientRect.bottom - m_wndClientRect.top;

	InitBackbuffer(m_screenContext, width, height);

	EndPaint(m_hwnd, &ps);
}

/////////////////////////////////////////////////////

void Renderer::Resize(Point size)
{
	Init();
}

/////////////////////////////////////////////////////

void Renderer::InitBackbuffer(HDC context, int width, int height)
{
	m_offscreenHdc = CreateCompatibleDC(context);
	m_offscreenBitmap = CreateCompatibleBitmap(context, width, height);
}

/////////////////////////////////////////////////////
