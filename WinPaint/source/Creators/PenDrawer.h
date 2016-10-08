#pragma once
#include "BaseCreator.h"

namespace paint
{
	class PenDrawer : public ICreator
	{
	public:
		virtual void OnPress(int x, int y) override;
		virtual void OnRelease(int x, int y) override;
		virtual void OnMove(int x, int y) override;
		virtual void OnDoubleClick(int x, int y) override;

		virtual Tool GetTool() override { return Tool::Pen; }
	};
}