#include "stdafx.h"
#include "AppContext.h"
#include "Creators/LineCreator.h"
#include "Creators/PenDrawer.h"
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
}

/////////////////////////////////////////////////////

AppContext::AppContext(HWND hwnd)
	: m_hwnd(hwnd)
{
	m_renderer.reset(new Renderer(m_hwnd));

	auto sceneMgr = new SceneManager();
	sceneMgr->SetButtonsId(IDM_UNDO, IDM_REDO);

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
}

/////////////////////////////////////////////////////

void AppContext::InitToolbar()
{
	m_toolbar.reset(new Toolbar());

	m_toolbar->RegisterTool(Tool::Pen, new PenDrawer());
	m_toolbar->RegisterTool(Tool::Line, new LineCreator());

	m_toolbar->SelectTool(Tool::Line);

	// Register observers
	auto sceneMgr = SceneManager::GetInstance();

	m_toolbar->GetTool(Tool::Pen)->AddObserver(sceneMgr);
	m_toolbar->GetTool(Tool::Line)->AddObserver(sceneMgr);
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
