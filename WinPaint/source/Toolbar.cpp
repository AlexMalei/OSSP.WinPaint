#include "stdafx.h"
#include "Toolbar.h"
#include "AppContext.h"
#include <algorithm>

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
	CheckMenuTool(tool);
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

void Toolbar::CheckMenuTool(Tool tool)
{
	HWND hwnd = AppContext::GetInstance()->GetWindowHandle();
	HMENU menu = GetMenu(hwnd);

	// Uncheck all
	for (auto item : m_menuItemsAssoc)
	{
		CheckMenuItem(menu, item.first, MF_UNCHECKED);
	}

	auto predicate = [tool](std::pair<const DWORD, paint::Tool>& pair)
	{
		return (pair.second.value() == tool.value());
	};

	auto selectedItem = std::find_if(m_menuItemsAssoc.begin(), m_menuItemsAssoc.end(), predicate);
	if (selectedItem != m_menuItemsAssoc.end())
	{
		CheckMenuItem(menu, selectedItem->first, MF_CHECKED);
	}
}

/////////////////////////////////////////////////////

Tool Toolbar::GetToolByName(const char* name)
{
	for (auto it : m_tools)
	{
		Tool tool = static_cast<Tool::type>(it.first);
		if (strcmp(tool.name(), name) == 0)
		{
			return tool;
		}
	}

	return Tool::None;
}

/////////////////////////////////////////////////////
