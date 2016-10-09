#pragma once

namespace paint
{
	class IFactory
	{
	public:
		virtual void* Create() = 0;
	};

	template <class T>
	class Factory : public IFactory
	{
	public:
		virtual void* Create() override { return new T(); }
	};
}
