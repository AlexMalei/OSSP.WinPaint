#pragma once
#include "Observer.h"

namespace paint
{
	class CreationObserver : public Observer
	{
	public:
		virtual void NotifyCreationFinished() = 0;
		virtual void NotifyCreationStateChanged() = 0;
	};
}
