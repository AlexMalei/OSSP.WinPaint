#pragma once
#include "ToolDefs.h"
#include "System/ISerializable.h"

namespace paint
{
	class Shape : public ISerializable
	{
	public:
		virtual ~Shape() {}

		virtual Tool GetTool() = 0;

		virtual void Serialize(std::ostream& s) = 0;
		virtual void Deserialize(std::istream& s) = 0;

		virtual tinyxml2::XMLElement* ToXml(tinyxml2::XMLDocument* doc) = 0;
		virtual void FromXml(tinyxml2::XMLElement* element) = 0;
	};
}
