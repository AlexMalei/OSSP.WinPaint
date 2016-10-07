#include "stdafx.h"
#include "AppContext.h"
#include "Creators/LineCreator.h"
#include "InputManager.h"

using namespace paint;

/////////////////////////////////////////////////////
/// Input callbacks

namespace
{
	void OnMousePress(MouseButton button, Point mousePos)
	{
		auto creator = AppContext::GetInstance()->GetCurrentCreator();
		creator->OnPress(mousePos.x, mousePos.y);
	}

	/////////////////////////////////////////////////////

	void OnMouseRelease(MouseButton button, Point mousePos)
	{
		auto creator = AppContext::GetInstance()->GetCurrentCreator();
		creator->OnRelease(mousePos.x, mousePos.y);
	}

	/////////////////////////////////////////////////////

	void OnMouseMove(Point mousePos)
	{
		auto creator = AppContext::GetInstance()->GetCurrentCreator();
		creator->OnMove(mousePos.x, mousePos.y);
	}
}

/////////////////////////////////////////////////////

AppContext::AppContext(HWND hwnd)
	: m_hwnd(hwnd)
{
	m_currentCreator.reset(new LineCreator());

	m_renderer.reset(new Renderer(m_hwnd));
	m_renderer->SetActiveCreator(m_currentCreator);
	m_currentCreator->AddObserver(m_renderer.get());

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
