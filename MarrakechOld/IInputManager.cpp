#include "stdafx.h"
#include "IInputManager.h"
#include "IEffectManager.h"
#include "CCamera.h"
#include "Globals.h"
#include <windows.h>


IInputManager * IInputManager::ms_pIntance = NULL;

void IInputManager::ManageInput(unsigned char key, bool isPressed, CCamera * cam)
{
	if (isPressed)
	{
		switch (key)
		{
		case 'W':
			cam->Walk(CCamera::CM_FORWARD);
			break;
		case 'S':
			cam->Walk(CCamera::CM_BACKWARD);
			break;
		case 'A':
			cam->Strafe(CCamera::CM_LEFT);
			break;
		case 'D':
			cam->Strafe(CCamera::CM_RIGHT);
			break;
		case 'X':
			cam->Fly(CCamera::CM_UP);
			break;
		case 'Z':
			cam->Fly(CCamera::CM_DOWN);
			break;

		case VK_UP:
			cam->Pitch(CCamera::CR_UP);
			break;
		case VK_DOWN:
			cam->Pitch(CCamera::CR_DOWN);
			break;
		case VK_LEFT:
			cam->Yaw(CCamera::CR_LEFT);
			break;
		case VK_RIGHT:
			cam->Yaw(CCamera::CR_RIGHT);
			break;

		case '1':
			Globals::currentEffect = BLACK_AND_WHITE;
			break;
		case '2':
			Globals::currentEffect = BLUR;
			break;
		case '3':
			Globals::currentEffect = BLOOM;
			break;
		case '4':
			Globals::currentEffect = DEPTH_OF_FIELD;
			break;
		case '5':
			Globals::currentEffect = SEPIA;
			break;
		case '6':
			Globals::currentEffect = SOBEL_EDGE_DETECTION;
			break;
		case '7':
			Globals::currentEffect = SKY_BOX_TV;
			break;
		case '0':
			Globals::currentEffect = NO_EFFECTS;
			break;
		}
	}
}