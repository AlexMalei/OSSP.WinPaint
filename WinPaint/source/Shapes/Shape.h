#pragma once
#include "ToolDefs.h"
#include "System/ISerializable.h"
#include "System/IXmlConvertable.h"
#include "Shapes/ShapeStyle.h"

namespace paint
{
	class Shape : public ISerializable, public IXmlConvertable
	{
	public:
		virtual ~Shape() {}

		COLORREF GetPenColor() const { return m_style.m_penColor; }
		COLORREF GetBrushColor() const { return m_style.m_brushColor; }
		DWORD GetLineThickness() const { return m_style.m_penThickness; }
		void SetPenColor(COLORREF color) { m_style.m_penColor = color; }
		void SetBrushColor(COLORREF color) { m_style.m_brushColor = color; }
		void SetLineThickness(DWORD thickness) { m_style.m_penThickness = thickness; }
		const ShapeStyle& GetStyle() const { return m_style; }
		void SetStyle(const ShapeStyle& style) { m_style = style; }

		virtual Tool GetTool() = 0;

		virtual void Serialize(std::ostream& s) = 0;
		virtual void Deserialize(std::istream& s) = 0;

		virtual tinyxml2::XMLElement* ToXml(tinyxml2::XMLDocument* doc) = 0;
		virtual void FromXml(tinyxml2::XMLElement* element) = 0;

	protected:
		ShapeStyle m_style;
	};
}
