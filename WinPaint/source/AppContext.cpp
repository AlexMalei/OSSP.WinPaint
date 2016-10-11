#include "stdafx.h"
#include "AppContext.h"
#include "Creators/LineCreator.h"
#include "Creators/PenDrawer.h"
#include "Creators/RectangleCreator.h"
#include "Creators/EllipseCreator.h"
#include "Creators/PolylineCreator.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "resource.h"

using namespace paint;

/////////////////////////////////////////////////////
/// Input callbacks

namespace
{
	void OnMousePress(MouseButton button, Point mousePos)
	{
		auto creator = AppContext::GetInstance()->GetCurrentTool();
		creator->OnPress(mousePos.x, mousePos.y);
	}

	/////////////////////////////////////////////////////

	void OnMouseRelease(MouseButton button, Point mousePos)
	{
		auto creator = AppContext::GetInstance()->GetCurrentTool();
		creator->OnRelease(mousePos.x, mousePos.y);
	}

	/////////////////////////////////////////////////////

	void OnMouseMove(Point mousePos)
	{
		auto creator = AppContext::GetInstance()->GetCurrentTool();
		creator->OnMove(mousePos.x, mousePos.y);
	}

	/////////////////////////////////////////////////////

	void OnKeyPress(DWORD keyCode)
	{
		auto creator = AppContext::GetInstance()->GetCurrentTool();
		creator->OnKeyPress(keyCode);
	}
}

/////////////////////////////////////////////////////

AppContext::AppContext(HWND hwnd)
	: m_hwnd(hwnd)
{
	m_renderer.reset(new Renderer(m_hwnd));

	auto sceneMgr = new SceneManager();
	sceneMgr->SetButtonsId(IDM_UNDO, IDM_REDO, IDM_SAVE);

	InitToolbar();
	InitInputManager();
}

/////////////////////////////////////////////////////

AppContext::~AppContext()
{
	Cleanup();
}

/////////////////////////////////////////////////////

void AppContext::Cleanup()
{
	InputManager::FreeInstance();
	SceneManager::FreeInstance();
}

/////////////////////////////////////////////////////

void AppContext::InitInputManager()
{
	auto inputMgr = new InputManager();
	inputMgr->AddMousePressCallback(&OnMousePress);
	inputMgr->AddMouseReleaseCallback(&OnMouseRelease);
	inputMgr->AddMouseMoveCallback(&OnMouseMove);
	inputMgr->AddKeyPressCallback(&OnKeyPress);
}

/////////////////////////////////////////////////////

void AppContext::InitToolbar()
{
	auto sceneMgr = SceneManager::GetInstance();
	m_toolbar.reset(new Toolbar());

	m_toolbar->RegisterTool(Tool::Pen, new PenDrawer())->AddObserver(sceneMgr);
	m_toolbar->RegisterTool(Tool::Line, new LineCreator())->AddObserver(sceneMgr);
	m_toolbar->RegisterTool(Tool::Ellipse, new EllipseCreator())->AddObserver(sceneMgr);
	m_toolbar->RegisterTool(Tool::Rectangle, new RectangleCreator())->AddObserver(sceneMgr);
	m_toolbar->RegisterTool(Tool::Polyline, new PolylineCreator())->AddObserver(sceneMgr);
}

/////////////////////////////////////////////////////

void AppContext::OnRender()
{
	m_renderer->Render();
}

/////////////////////////////////////////////////////

void AppContext::OnResize(Point size)
{
	m_renderer->Resize(size);
}

/////////////////////////////////////////////////////
