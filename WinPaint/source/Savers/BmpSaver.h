#pragma once
#include "IBitmapSaver.h"

namespace paint
{
	class BmpSaver : public IBitmapSaver
	{
	public:
		virtual bool Save(BITMAP bmp) override;
	};
}
