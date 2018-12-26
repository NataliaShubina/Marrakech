#pragma once
#include "Widget.h"

class ButtonWidget : public Widget
{

public:

	virtual void OnKeyPressed() override {};
	virtual void OnKeyReleased() override {};

private:
	bool	m_isActive {true};
};