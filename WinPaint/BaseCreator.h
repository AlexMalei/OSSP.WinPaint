#pragma once
#include "Shape.h"
#include "Observable.h"
#include "CreationObserver.h"

namespace paint
{
	class ICreator : public Observable<CreationObserver>
	{
	public:
		virtual void OnPress(int x, int y) = 0;
		virtual void OnRelease(int x, int y) = 0;
		virtual void OnMove(int x, int y) = 0;
		virtual void OnDoubleClick(int x, int y) = 0;

		Shape* GetShape() { return m_createdShape; }

	protected:
		Shape* m_createdShape;
	};
}
