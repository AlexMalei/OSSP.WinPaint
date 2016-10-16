#pragma once
#include "System/IXmlConvertable.h"

namespace paint
{
	class Font : public IXmlConvertable
	{
	public:
		Font();
		Font(LPLOGFONTA logicFont);
		~Font();

		HFONT GetHandle() const { return m_font; }
		void Apply(HDC hdc) { SelectObject(hdc, m_font); }

		bool IsBold() const;
		bool IsItalic() const;
		bool IsUnderlined() const;
		LPSTR GetFace() const;
		DWORD GetSize() const;

		virtual tinyxml2::XMLElement* ToXml(tinyxml2::XMLDocument* doc) override;
		virtual void FromXml(tinyxml2::XMLElement* element) override;

	private:
		HFONT m_font;

		LPSTR m_face;
		LONG m_sizeX;
		LONG m_sizeY;
		LONG m_weight;
		BYTE m_italic;
		BYTE m_underlined;
	};
}