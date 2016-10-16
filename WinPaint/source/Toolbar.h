#pragma once
#include "Creators/BaseCreator.h"
#include "Shapes/Font.h"
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

		COLORREF GetPenColor() const { return m_style.m_penColor; }
		COLORREF GetBrushColor() const { return m_style.m_brushColor; }
		DWORD GetLineThickness() const { return m_style.m_penThickness; }
		std::shared_ptr<Font> GetFont() const { return m_font; }
		void SetPenColor(COLORREF color) { m_style.m_penColor = color; }
		void SetBrushColor(COLORREF color) { m_style.m_brushColor = color; }
		void SetLineThickness(DWORD thickness) { m_style.m_penThickness = thickness; }
		void SetFont(std::shared_ptr<Font> font) { m_font = font; }

	private:
		ICreator* InternalGetTool(Tool tool) const;
		void CheckMenuTool(Tool tool);
		void InitDefaultFont();

		std::unordered_map<int, ICreator*> m_tools;
		std::unordered_map<DWORD, Tool> m_menuItemsAssoc;
		ICreator* m_activeTool = nullptr;
		ShapeStyle m_style;
		std::shared_ptr<Font> m_font;
	};
}
