#include "stdafx.h"
#include "Renderer.h"
#include "Line.h"

using namespace paint;

Renderer::Renderer(HWND hWnd)
	: m_hwnd(hWnd)
{
	Init();

	auto shape = new paint::Line(paint::Point(25, 50), paint::Point(150, 75));
	m_shapes.push_back(shape);
}

void Renderer::NotifyCreationFinished()
{
	m_shapes.push_back(m_currentCreator->GetShape());

	InvalidateRect(m_hwnd, nullptr, TRUE);
}

void Renderer::NotifyCreationStateChanged()
{
	InvalidateRect(m_hwnd, nullptr, TRUE);
}

void Renderer::Render()
{
	m_screenContext = BeginPaint(m_hwnd, m_ps);

	HBITMAP oldBitmap = static_cast<HBITMAP>(SelectObject(m_offscreenHdc, m_offscreenBitmap));

	// Fill backbuffer with system color
	HBRUSH hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	FillRect(m_offscreenHdc, &m_wndClientRect, hbrBkGnd);
	DeleteObject(hbrBkGnd);

	// [ RENDER ]

	for (auto shape : m_shapes)
	{
		RenderShape(m_offscreenHdc, shape);
	}

	auto currentCreatorShape = m_currentCreator->GetShape();
	if (currentCreatorShape)
	{
		RenderShape(m_offscreenHdc, currentCreatorShape);
	}

	// [ RENDER ]

	int width = m_wndClientRect.right - m_wndClientRect.left;
	int height = m_wndClientRect.bottom - m_wndClientRect.top;

	BitBlt(m_screenContext, m_wndClientRect.left, m_wndClientRect.top, width, height, m_offscreenHdc, 0, 0, SRCCOPY);

	// Swap buffers
	SelectObject(m_offscreenHdc, oldBitmap);

	EndPaint(m_hwnd, m_ps);
}

void Renderer::RenderShape(HDC hdc, Shape* shape)
{
	auto shapeType = shape->GetType();

	switch (shapeType)
	{
	case paint::ShapeType::Line:
		paint::Line* line = static_cast<paint::Line*>(shape);

		auto topLeft = line->GetTopLeft();
		auto bottomRight = line->GetRightBottom();

		MoveToEx(hdc, topLeft.x, topLeft.y, NULL);
		LineTo(hdc, bottomRight.x, bottomRight.y);

		break;
	}
}

void Renderer::Init()
{
	m_ps = new PAINTSTRUCT();

	m_screenContext = BeginPaint(m_hwnd, m_ps);

	GetClientRect(m_hwnd, &m_wndClientRect);
	int width = m_wndClientRect.right - m_wndClientRect.left;
	int height = m_wndClientRect.bottom - m_wndClientRect.top;

	// Create back buffer
	m_offscreenHdc = CreateCompatibleDC(m_screenContext);
	m_offscreenBitmap = CreateCompatibleBitmap(m_screenContext, width, height);

	EndPaint(m_hwnd, m_ps);
}
