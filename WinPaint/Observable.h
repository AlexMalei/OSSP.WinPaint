#pragma once
#include "Observer.h"
#include <vector>

namespace paint
{
	template <class T>
	class Observable
	{
		typedef void (T::*method)(void);

	public:
		void AddObserver(T* observer) { m_observers.push_back(observer); }

		void RemoveObserver(T* observer)
		{
			auto it = std::find(m_observers.begin(), m_observers.end(), observer);
			if (it != m_observers.end())
			{
				m_observers.erase(it);
			}	
		}

		void NotifyAll(method m)
		{
			for (auto observer : m_observers)
			{
				(observer->*m)();
			}
		}

	protected:
		std::vector<T*> m_observers;
	};
}