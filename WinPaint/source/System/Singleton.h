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
			s_instance = this;
		}

		static void FreeInstance()
		{
			delete s_instance;
			s_instance = nullptr;
		}

		static T* GetInstance()
		{
			return static_cast<T*>(s_instance);
		}

	private:
		static Singleton<T>* s_instance;
	};

	template <class T>
	Singleton<T>* Singleton<T>::s_instance = nullptr;
}
