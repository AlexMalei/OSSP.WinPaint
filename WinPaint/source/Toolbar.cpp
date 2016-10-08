#include "stdafx.h"
#include "Toolbar.h"

using namespace paint;

/////////////////////////////////////////////////////

Toolbar::Toolbar()
{

}

/////////////////////////////////////////////////////

ICreator* Toolbar::GetTool(Tool tool) const
{	
	return InternalGetTool(tool);
}

/////////////////////////////////////////////////////

void Toolbar::RegisterTool(Tool toolType, ICreator* creator)
{
	auto mapTool = InternalGetTool(toolType);
	if (!mapTool)
	{
		int toolId = toolType.value();
		m_tools.insert(std::pair<int, ICreator*>(toolId, creator));
	}
}

/////////////////////////////////////////////////////

void Toolbar::SelectTool(Tool tool)
{
	m_activeTool = InternalGetTool(tool);
}

/////////////////////////////////////////////////////

ICreator* Toolbar::InternalGetTool(Tool tool) const
{
	int toolId = tool.value();
	auto it = m_tools.find(toolId);
	if (it != m_tools.end())
	{
		return it->second;
	}

	return nullptr;
}

/////////////////////////////////////////////////////
