#pragma once
#include <ostream>
#include <istream>

namespace paint
{
	class ISerializable
	{
	public:
		virtual void Serialize(std::ostream& s) = 0;
		virtual void Deserialize(std::istream& s) = 0;
	};
}
