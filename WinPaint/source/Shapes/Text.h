#pragma once
#include "Shape.h"
#include "Point.h"
#include "Font.h"

namespace paint
{
	class Text : public Shape
	{
	public:
		Text();
		Text(int x, int y);
		Text(Point topLeft);
		Text(int x, int y, const std::string& text);
		Text(Point topLeft, const std::string& text);

		Point GetTopLeft() { return m_topLeft; }
		void SetTopLeft(const Point& p) { m_topLeft = p; }
		const std::string& GetText() const { return m_text; }
		void SetText(const std::string& str) { m_text = str; }
		void Append(const char c) { m_text += c; }
		void Append(const char* str) { m_text += str; }
		void Append(const std::string& str) { m_text += str; }
		void EraseLast();

		void SetColor(COLORREF color) { m_color = color; }
		COLORREF GetColor() const { return m_color; }
		void SetFont(std::shared_ptr<Font> font) { m_font = font; }
		std::shared_ptr<Font> GetFont() const { return m_font; }

		virtual Tool GetTool() override { return Tool::Text; }

		virtual void Serialize(std::ostream& s) override;
		virtual void Deserialize(std::istream& s) override;

		virtual tinyxml2::XMLElement* ToXml(tinyxml2::XMLDocument* doc) override;
		virtual void FromXml(tinyxml2::XMLElement* element) override;

		void operator << (char c) { Append(c); }
		void operator << (const char* str) { Append(str); }
		void operator << (const std::string& str) { Append(str); }

	protected:
		Point m_topLeft;
		std::string m_text;
		COLORREF m_color;
		std::shared_ptr<Font> m_font;
	};
}
