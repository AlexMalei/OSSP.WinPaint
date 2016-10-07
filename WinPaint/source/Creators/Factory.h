#pragma once

namespace paint
{
	class BaseFactory
	{
	public:
		virtual void* Create() = 0;
	};

	template <class T>
	class Factory : public BaseFactory
	{
	public:
		virtual void* Create() override { return new T(); }
	};
}
