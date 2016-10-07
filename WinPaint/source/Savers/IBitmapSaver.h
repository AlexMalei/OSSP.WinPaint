#pragma once
#include "stdafx.h"

namespace paint
{
	class IBitmapSaver
	{
	public:
		virtual bool Save(BITMAP bmp) = 0;
	};
}
