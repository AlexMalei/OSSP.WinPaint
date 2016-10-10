#pragma once
#include "Shapes/Shape.h"
#include "Observers/Observable.h"
#include "Observers/CreationObserver.h"
#include "ToolDefs.h"

namespace paint
{
	class ICreator : public Observable<CreationObserver>
	{
	public:
		virtual void OnPress(int x, int y) = 0;
		virtual void OnRelease(int x, int y) = 0;
		virtual void OnMove(int x, int y) = 0;
		virtual void OnDoubleClick(int x, int y) = 0;
		virtual void OnKeyPress(DWORD keyCode) = 0;

		virtual void Update() {}

		Shape* GetShape() { return m_createdShape; }
		virtual Tool GetTool() = 0;

	protected:
		Shape* m_createdShape;
	};
}
