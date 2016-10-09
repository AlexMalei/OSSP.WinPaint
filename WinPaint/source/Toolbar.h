#pragma once
#include "Creators/BaseCreator.h"
#include <unordered_map>

namespace paint
{
	class Toolbar
	{
	public:
		Toolbar();

		ICreator* RegisterTool(Tool toolType, ICreator* creator);
		void SelectTool(Tool tool);

		ICreator* GetTool(Tool tool) const;

		ICreator* GetCurrentTool() const { return m_activeTool; }
		Tool GetCurrentToolDef() const { return m_activeTool->GetTool(); }

		void LoadMenuItemLinks(std::unordered_map<DWORD, Tool>& links) { m_menuItemsAssoc = links; }

		Tool GetToolByName(const char* name);

	private:
		ICreator* InternalGetTool(Tool tool) const;
		void CheckMenuTool(Tool tool);

		std::unordered_map<int, ICreator*> m_tools;
		std::unordered_map<DWORD, Tool> m_menuItemsAssoc;
		ICreator* m_activeTool = nullptr;
	};
}
