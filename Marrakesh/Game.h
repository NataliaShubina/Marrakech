#pragma once
#include "Util/include/Application.h"

#include "source/Managers/MeshLoader.h"
#include "source/Managers/ShaderLoader.h"
#include "source/Managers/TextureLoader.h"
#include "source/Managers/TimeManager.h"
#include "source/Managers/InputManager.h"

#include "source/Entity/Mesh.h"
#include "source/Entity/Terrain.h"
#include "source/Entity/Texture.h"

#include "source/Game/Camera.h"
#include "source/Game/Scene.h"
#include "source/Game/Object.h"
#include "source/Game/StateMatch.h"
#include "source/Game/StateMenu.h"

#include <stdio.h>

#include "../Utilities/utilities.h"


class Game : public Application
{
	enum GameState
	{
		IDLE,
		LOAD
	};

public:

	static Game * GetInstance() { return m_game; }

	int Init(ESContext *esContext, Game * game);

	int Startup(ESContext *esContext);
	void Shutdown() override;

	void Render(ESContext *esContext);
	void Update(ESContext *esContext, float deltaTime);
	void OnKey(ESContext *esContext, unsigned char key, bool bIsPressed);
	void OnMousePressed();
	void OnMouseReleased();

	void SetState(GameState state);
	GameState GetState() const { return m_state; }

	SharedPtr<State> GetCurrentState() const { return m_stateStack.rbegin()->second; }

	void PushState(const char * key);
	void PopState();

protected:


	static void Render_Callback(ESContext *esContext);
	static void Update_Callback(ESContext *esContext, float deltaTime);
	static void OnKey_Callback(ESContext *esContext, unsigned char key, bool bIsPressed);
	static void OnMousePress_callback(ESContext *esContext);
	static void OnMouseRelease_callback(ESContext *esContext);

	static Game * m_game;

private:

	GameState m_state{ IDLE };

	SharedPtr<StateMatch> m_match;

	PMap<const char*, SharedPtr<State>> m_stateStack;
};
