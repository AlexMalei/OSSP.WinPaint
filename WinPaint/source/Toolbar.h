#pragma once
#include "Creators/BaseCreator.h"
#include <unordered_map>

namespace paint
{
	class Toolbar
	{
	public:
		Toolbar();

		void RegisterTool(Tool toolType, ICreator* creator);
		void SelectTool(Tool tool);

		ICreator* GetTool(Tool tool) const;

		ICreator* GetCurrentTool() const { return m_activeTool; }
		Tool GetCurrentToolDef() const { return m_activeTool->GetTool(); }

	private:
		ICreator* InternalGetTool(Tool tool) const;

		std::unordered_map<int, ICreator*> m_tools;
		ICreator* m_activeTool = nullptr;
	};
}
