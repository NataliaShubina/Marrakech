#pragma once
#include "SFog.h"
#include "SAmbientLight.h"

class CObject;
class CCamera;
class CLight;
class CCharacterFactory;
class CEnvironmentFactory;

class ISceneManager
{
protected:
	ISceneManager() {}
	~ISceneManager() { Release(); }

	ISceneManager(const ISceneManager&) {}
	ISceneManager operator =(const ISceneManager&) {}

public:
	static ISceneManager * GetInstance()
	{
		if (ms_pIntance == nullptr)
			ms_pIntance = new ISceneManager;
		return ms_pIntance;		
	}
	static void DestroyInstance()
	{
		if (ms_pIntance)
		{
			delete ms_pIntance;
			ms_pIntance = 0;
		}
	}


	int Load(const char * path, const char * objData);
	void Draw();
	void Update(float deltatime);
	CCamera * GetCamera() const { return m_pSceneCamera; }

protected:
	static ISceneManager * ms_pIntance;

private:
	unsigned int m_uNumOfObjects;

	unsigned int m_uNumOfLights;

	CObject ** m_pSceneObjects;

	//CCharacterFactory * m_pCharFactory;
	//CEnvironmentFactory * m_pEnvFactory;

	CCamera * m_pSceneCamera;

	CLight ** m_pLights;
	SAmbientLight m_ambLight;

	SFog m_fog;

	void Release();
};
