#pragma once

// Templatized singleton pattern implementation

namespace paint
{
	template <class T>
	class Singleton
	{
	public:
		// Simple constructor is used instead of some sort of CreateInstance() method
		Singleton()
		{
			s_instance = static_cast<T*>(this);
		}

		static void FreeInstance()
		{
			delete s_instance;
			s_instance = nullptr;
		}

		static T* GetInstance()
		{
			return s_instance;
		}

	protected:
		~Singleton() {}
		Singleton(Singleton& ref) {}

		static T* s_instance;
	};

	template <class T>
	T* Singleton<T>::s_instance = nullptr;
}
