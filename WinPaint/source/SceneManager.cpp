#include "stdafx.h"
#include "SceneManager.h"
#include "AppContext.h"

using namespace paint;

/////////////////////////////////////////////////////

SceneManager::SceneManager()
{
	
}

/////////////////////////////////////////////////////

SceneManager::~SceneManager()
{

}

/////////////////////////////////////////////////////

void SceneManager::NotifyCreationFinished()
{
	auto context = AppContext::GetInstance();

	auto activeTool = context->GetCurrentTool();
	m_shapes.push_back(activeTool->GetShape());

	context->GetRenderer()->Refresh();
}

/////////////////////////////////////////////////////

void SceneManager::NotifyCreationStateChanged()
{
	auto context = AppContext::GetInstance();
	auto currentShape = context->GetCurrentTool()->GetShape();

	auto shapesCount = m_shapes.size();
	if ((shapesCount == 0) || (currentShape != m_shapes[shapesCount - 1]))
	{
		m_shapes.push_back(currentShape);
	}

	AppContext::GetInstance()->GetRenderer()->Refresh();
}

/////////////////////////////////////////////////////
