#pragma once
#include "Widget.h"

class TextWidget : public Widget
{
public:

	virtual void OnKeyPressed() override {};
	virtual void OnKeyReleased() override {};

private:

	//... text
};