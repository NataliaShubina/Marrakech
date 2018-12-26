#pragma once

#include "../Marrakesh/Util/include/Singleton.h"
#include "../Utilities/utilities.h"
#include "../Marrakesh/Util/Math.h"

class Camera;

class InputManager: public Singleton<InputManager>
{
public:
	void ManageKeyboard(ESContext *esContext, unsigned char key, bool isPressed, Camera * cam);
	void ManageCursor(ESContext *esContext);
	void MousePressed(ESContext *esContext, unsigned char key);
	void MouseReleased(ESContext *esContext, unsigned char key);

	math::vec2 GetPointerPosition() const { return m_pointerPosition; }

protected:

	void CalculateRay(Camera * cam);

private:

	math::vec2 m_pointerPosition;

	math::vec3 m_normalizedCursor;
	math::vec3 m_rayWorld;

	math::vec4 m_rayClip;
	math::vec4 m_rayEye;
	
	
};