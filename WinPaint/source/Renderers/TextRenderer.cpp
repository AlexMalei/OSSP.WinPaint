#pragma once
#include "stdafx.h"
#include "TextRenderer.h"
#include "Shapes/Text.h"
#include "AppContext.h"

using namespace paint;

/////////////////////////////////////////////////////

void TextRenderer::Render(Shape* shape)
{
	Text* text = static_cast<Text*>(shape);

	auto topLeft = text->GetTopLeft();
	auto textValue = text->GetText();

	AppContext::GetInstance()->GetRenderer()->DrawText(topLeft, textValue.c_str(), textValue.length());
}

/////////////////////////////////////////////////////
