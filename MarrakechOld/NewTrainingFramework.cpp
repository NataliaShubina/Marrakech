// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Globals.h"
#include "IResourceManager.h"
#include "ISceneManager.h"
#include "IInputManager.h"
#include "IEffectManager.h"
#include "CCamera.h"
#include "CPostPShader.h"
#include "CFbo.h"
#include "Vertex.h"
#include "CShaders.h"

#include <stdio.h>

#include "../Utilities/utilities.h"

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	IResourceManager::GetInstance()->LoadEngineResources("../Resources/RM.json");
	ISceneManager::GetInstance()->Load("../Resources/SM.json", "../Resources/Objects.json");
	IEffectManager::GetInstance()->LoadEffects("../Resources/EM.json");

	return 0;
}


void Draw ( ESContext *esContext )
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ISceneManager::GetInstance()->GetCamera()->ComputeMatrices();

	if (Globals::currentEffect == NO_EFFECTS)
	{
		ISceneManager::GetInstance()->Draw();

	}
	else
	{
		for (int i = 0; i < IEffectManager::GetInstance()->GetFBONum()-4; i++)
		{
			IEffectManager::GetInstance()->GetFBOById(i)->BindFBO();
			ISceneManager::GetInstance()->Draw();
		}
		for (int i = 0; i < IEffectManager::GetInstance()->GetFBONum(); i++)
		{
			IEffectManager::GetInstance()->GetFBOById(i)->UnbindFBO();
		}
		if (Globals::currentEffect != SKY_BOX_TV)
		{
			IEffectManager::GetInstance()->Draw(Globals::currentEffect);
		}
		else
		{
			static bool isDrawed = false;
			if (!isDrawed)
			{
				IEffectManager::GetInstance()->Draw(SKY_BOX_TV);
				isDrawed = true;
			}
			ISceneManager::GetInstance()->Draw();
			IEffectManager::GetInstance()->DrawBox();
		}
	}

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	Globals::m_time += deltaTime;
	ISceneManager::GetInstance()->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	IInputManager::GetInstance()->ManageInput(key, bIsPressed, ISceneManager::GetInstance()->GetCamera());
}

void CleanUp()
{
	ISceneManager::DestroyInstance();
	IResourceManager::DestroyInstance();
	IEffectManager::DestroyInstance();
	IInputManager::DestroyInstance();
}

//////////////////////////////////////////// WINDOWS main function ////////////////////////////////////////////////////
#ifdef _WIN32

#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	printf("Press any key...\n");
	_getch();

	return 0;
}

#endif
//////////////////////////////////////////// WINDOWS main function ////////////////////////////////////////////////////
