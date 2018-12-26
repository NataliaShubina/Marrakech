#pragma once
#include "../Marrakesh/Util/Math.h"

#define LBUTTON 0x01
#define RBUTTON 0x02
#define MBUTTON 0x03

class State
{
public:
	State() {};
	virtual ~State() {};

	virtual int Init() = 0;
	virtual void SetupGui() = 0;
	virtual void Render() = 0;
	virtual void OnKeyPressed() = 0;
	virtual void OnKeyReleased() = 0;
	virtual void OnMouseBtn(char btn, bool pressed, const math::vec3& position) = 0;
protected:
	virtual void RenderGui() = 0;
};