#pragma once

namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
}

namespace paint
{
	class IXmlConvertable
	{
	public:
		virtual tinyxml2::XMLElement* ToXml(tinyxml2::XMLDocument* doc) = 0;
		virtual void FromXml(tinyxml2::XMLElement* element) = 0;
	};
}
