#include "InputManager.h"
#include "../Game/Camera.h"
#include "../Marrakesh/Util/include/Defines.h"
#include "../Marrakesh/Util/Math.h"
#include "GL/gl3w.h"
#include "GL/glcorearb.h"
#include "GLFW/glfw3.h"
#include "../Marrakesh/Game.h"

#include <Windows.h>
#include <stdio.h>


void InputManager::CalculateRay(Camera * cam)
{
	float x = (2.0f * m_pointerPosition.x) / WINDOW_WIDTH - 1.0f;
	float y = 1.0f - (2.0f * m_pointerPosition.y) / WINDOW_HEIGHT;

	m_normalizedCursor = math::vec3(x, y, 1.0f);

	m_rayClip = math::vec4(x, y, -1.0, 1.0);

	m_rayEye = cam->GetProjMatrix().Inverse() * m_rayClip;
	m_rayEye.z = -1.0f;
	m_rayEye.w = 0.0f;

	auto rw = cam->GetViewMatrix().Inverse() * m_rayEye;
	m_rayWorld = math::vec3(rw.x, rw.y, rw.z);
	
	m_rayWorld.Normalize();
}


void InputManager::ManageKeyboard(ESContext *esContext, unsigned char key, bool isPressed, Camera * cam)
{
	POINT p;
	if (isPressed)
	{
		switch (key)
		{
		case 'W':
			cam->Walk(Camera::CM_FORWARD, 0.1f);
			break;
		case 'S':
			cam->Walk(Camera::CM_BACKWARD, 0.1f);
			break;
		case 'A':
			cam->Strafe(Camera::CM_LEFT, 0.1f);
			break;
		case 'D':
			cam->Strafe(Camera::CM_RIGHT, 0.1f);
			break;
		case 'X':
			cam->Fly(Camera::CM_UP, 0.1f);
			break;
		case 'Z':
			cam->Fly(Camera::CM_DOWN, 0.1f);
			break;

		case VK_UP:
			cam->Pitch(Camera::CR_UP, 1.0f);
			break;
		case VK_DOWN:
			cam->Pitch(Camera::CR_DOWN, 1.0f);
			break;
		case VK_LEFT:
			cam->Yaw(Camera::CR_LEFT, 1.0f);
			break;
		case VK_RIGHT:
			cam->Yaw(Camera::CR_RIGHT, 1.0f);
			break;

		case VK_LBUTTON:

			if (GetCursorPos(&p))
			{
				ScreenToClient(esContext->hWnd, &p);
				printf("Cursor position %d, %d\n", p.x, p.y);
				if (p.x < WINDOW_WIDTH && p.y < WINDOW_HEIGHT)
				{
					m_pointerPosition.x = p.x;
					m_pointerPosition.y = p.y;

					CalculateRay(cam);
					Game::GetInstance()->GetCurrentState()->OnMouseBtn(LBUTTON, true, m_rayWorld);
				}
			}
			break;

		}
	}
}

void InputManager::MousePressed(ESContext *esContext, unsigned char key)
{
	POINT p;
	switch (key)
	{
	case VK_LBUTTON:

		if (GetCursorPos(&p))
		{
			ScreenToClient(esContext->hWnd, &p);
			printf("Cursor position %d, %d\n", p.x, p.y);
			if (p.x < WINDOW_WIDTH && p.y < WINDOW_HEIGHT)
			{
				m_pointerPosition.x = p.x;
				m_pointerPosition.y = p.y;
			}
		}
		break;
	}
}

void InputManager::MouseReleased(ESContext *esContext, unsigned char key)
{

}

void InputManager::ManageCursor(ESContext *esContext)
{
	POINT p; //cursor
	if (GetCursorPos(&p))
	{
		ScreenToClient(esContext->hWnd, &p);
		printf("Cursor position %d, %d\n", p.x, p.y);
	}
}