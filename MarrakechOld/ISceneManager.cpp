#include "stdafx.h"
#include "ISceneManager.h"
#include "CObject.h"
#include "CCamera.h"
#include "CShaders.h"
#include "CModel.h"
#include "CLight.h"
#include "Globals.h"
#include "CCharacterFactory.h"
#include "CEnvironmentFactory.h"

#include <string>
#include <stdio.h>
#include <fstream>
#include <string>

#include "jsoncpp/json/json.h"

ISceneManager * ISceneManager::ms_pIntance = NULL;

int ISceneManager::Load(const char * path, const char * objData)
{
	std::ifstream file(path);

	if (!file.is_open())
	{
		return -1;
	}

	Json::Value jobj;
	Json::Reader reader;

	bool parsingResult = reader.parse(file, jobj);
	if (!parsingResult)
	{
		return -2;
	}

	
	////////////////////////////////////////////////////////////////       loading objects         ////////////////////////////////////////////////////////////////////////

	const Json::Value& objs = jobj["objects"];
	m_uNumOfObjects = objs.size();
	m_pSceneObjects = new CObject*[m_uNumOfObjects];

	unsigned int * textureCubeIndices;
	unsigned int * texture2dIndices;
	for (size_t i = 0; i < m_uNumOfObjects; i++)
	{
		m_pSceneObjects[i] = new CObject();

		//loading models
		m_pSceneObjects[i]->InitModel(objs[i]["model"].asInt());


		int dsize = objs[i]["2Dtex"].size();
		//loading 2d textures
		if (dsize > 0)
		{
			texture2dIndices = new unsigned int[dsize];
			for (size_t j = 0; j < dsize; j++)
			{
				texture2dIndices[j] = objs[i]["2Dtex"][j].asUInt();
			}
			m_pSceneObjects[i]->InitTextures2d(objs[i]["2Dtex"].size(), texture2dIndices);
			delete[] texture2dIndices;
		}


		int csize = objs[i]["cubeTex"].size();
		//loading Cube textures
		if (csize > 0)
		{
			textureCubeIndices = new unsigned int[csize];
			for (size_t j = 0; j < objs[i]["cubeTex"].size(); j++)
			{
				textureCubeIndices[j] = objs[i]["cubeTex"][j].asUInt();
			}
			m_pSceneObjects[i]->InitCubeTextures(objs[i]["cubeTex"].size(), textureCubeIndices);
			delete[] textureCubeIndices;
		}
		//loading shader
		m_pSceneObjects[i]->InitShader(objs[i]["shader"].asUInt());

		SParameters params;
		if (objs[i]["parameters"]["tiling_factor"])
		{
			params.tiling_factor = objs[i]["parameters"]["tiling_factor"].asFloat();
		}
		if (objs[i]["parameters"]["specular_power"])
		{
			params.specular_power = objs[i]["parameters"]["specular_power"].asFloat();
		}
		if (objs[i]["parameters"]["dMax"])
		{
			params.dMax = objs[i]["parameters"]["dMax"].asFloat();
		}
		if (objs[i]["parameters"]["depth_displ"])
		{
			params.depth_displ = objs[i]["parameters"]["depth_displ"].asFloat();
		}

		Vector3 pos = Vector3(objs[i]["position"][0].asFloat(), objs[i]["position"][1].asFloat(), objs[i]["position"][2].asFloat());
		Vector3 rot = Vector3(objs[i]["rotation"][0].asFloat(), objs[i]["rotation"][1].asFloat(), objs[i]["rotation"][2].asFloat());
		Vector3 scale = Vector3(objs[i]["scale"][0].asFloat(), objs[i]["scale"][1].asFloat(), objs[i]["scale"][2].asFloat());
		//loading moving param
		m_pSceneObjects[i]->InitObjectParams(objs[i]["moving"].asCString(), //loading move tipe
			pos, //loading position
			rot, //loading rotation
			scale, //loading scale
			params); //loading params 

		if (objs[i]["color"])
		{
			Vector3 color = Vector3(objs[i]["color"][0].asFloat(), objs[i]["color"][1].asFloat(), objs[i]["color"][2].asFloat());
			m_pSceneObjects[i]->SetColor(color);
		}
		m_pSceneObjects[i]->GetShader()->LocateParams();
	}

	//m_pCharFactory = new CCharacterFactory;
	//m_pCharFactory->LoadObjects(objData);
	//m_pEnvFactory = new CEnvironmentFactory;
	//m_pEnvFactory->LoadObjects(objData);

	////////////////////////////////////////////////////////////////       loading fog         ////////////////////////////////////////////////////////////////////////

	const Json::Value& jfog = jobj["fog"];
	m_fog.start = jfog["start"].asFloat();
	m_fog.range = jfog["range"].asFloat();
	m_fog.color = Vector3(jfog["color"][0].asFloat(), jfog["color"][1].asFloat(), jfog["color"][1].asFloat());

	////////////////////////////////////////////////////////////////       loading camera         ////////////////////////////////////////////////////////////////////////

	const Json::Value& cam = jobj["camera"];
	m_pSceneCamera = new CCamera();
	Vector3 pos = Vector3(cam["position"][0].asFloat(), cam["position"][1].asFloat(), cam["position"][2].asFloat());
	m_pSceneCamera->SetPosition(pos);
	m_pSceneCamera->SetLook(Vector3(0.0f, 0.0f, -1.0f));
	m_pSceneCamera->SetWorldUp(Vector3(0.0f, 1.0f, 0.0f));
	m_pSceneCamera->SetSpeed(cam["speed"].asFloat(), cam["rot_speed"].asFloat());
	m_pSceneCamera->SetVisibleArea(cam["fov"].asFloat(), cam["near"].asFloat(), cam["far"].asFloat());
	m_pSceneCamera->SetRotAngle(1.0f);
	m_pSceneCamera->ComputeMatrices();


	////////////////////////////////////////////////////////////////       loading lights         ////////////////////////////////////////////////////////////////////////

	const Json::Value& jamb = jobj["ambient_light"];
	m_ambLight.m_color = Vector3(jamb["color"][0].asFloat(), jamb["color"][1].asFloat(), jamb["color"][2].asFloat());
	m_ambLight.m_weight = jamb["weight"].asFloat();


	const Json::Value& jlights = jobj["lights"];
	m_uNumOfLights = jlights.size();
	m_pLights = new CLight*[m_uNumOfLights];
	for (size_t i = 0; i < m_uNumOfLights; i++)
	{
		m_pLights[i] = new CLight();

		if (!strcmp("directional", jlights[i]["type"].asCString()))
		{
			m_pLights[i]->SetType(0);
		}
		else if (!strcmp("point", jlights[i]["type"].asCString()))
		{
			m_pLights[i]->SetType(1);
		}
		Vector3 pos = Vector3(jlights[i]["pos_dir"][0].asFloat(), jlights[i]["pos_dir"][1].asFloat(), jlights[i]["pos_dir"][2].asFloat());
		m_pLights[i]->SetPosition(pos);

		Vector3 color = Vector3(jlights[i]["color"][0].asFloat(), jlights[i]["color"][1].asFloat(), jlights[i]["color"][2].asFloat());
		m_pLights[i]->SetColor(color);

		if (!strcmp("static", jlights[i]["type"].asCString()))
		{
			m_pLights[i]->SetMoveType(0);
		}

		if (!strcmp("circle", jlights[i]["type"].asCString()))
		{
			m_pLights[i]->SetMoveType(1);
		}

		m_pLights[i]->SetSpeed(jlights[i]["speed"].asFloat());
		m_pLights[i]->SetRadius(jlights[i]["radius"].asFloat());
	}

	return 0;
}


void ISceneManager::Draw()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	for (size_t i = 0; i < m_uNumOfObjects; i++)
	{
		m_pSceneObjects[i]->Draw((const CCamera*)m_pSceneCamera, m_uNumOfLights, (const CLight**) m_pLights,m_ambLight, m_fog);
	}

	//for (int i = 0; i < m_pEnvFactory->GetObjectNum(); i++)
	//{
	//	m_pEnvFactory->GetObjects()[i]->Draw((const CCamera*)m_pSceneCamera, m_uNumOfLights, (const CLight**)m_pLights, m_ambLight, m_fog);
	//}

	//for (int i = 0; i < m_pCharFactory->GetObjectNum(); i++)
	//{
	//	m_pCharFactory->GetObjects()[i]->Draw((const CCamera*)m_pSceneCamera, m_uNumOfLights, (const CLight**)m_pLights, m_ambLight, m_fog);
	//}
	glDisable(GL_DEPTH_TEST);
}

void ISceneManager::Update(float deltatime)
{
	for (size_t i = 0; i < m_uNumOfObjects; i++)
	{
		m_pSceneObjects[i]->Update(deltatime);
	}

	//for (int i = 0; i < m_pEnvFactory->GetObjectNum(); i++)
	//{
	//	m_pEnvFactory->GetObjects()[i]->Update(deltatime);
	//}

	//for (int i = 0; i < m_pCharFactory->GetObjectNum(); i++)
	//{
	//	m_pCharFactory->GetObjects()[i]->Update(deltatime);
	//}

	for (int i = 0; i < m_uNumOfLights; i++)
	{
		m_pLights[i]->Move(Vector3(0.0f,0.0f,0.0f));
	}
}

void ISceneManager::Release()
{
	SAFEDEL(m_pSceneCamera);

	for (int i = 0; i < m_uNumOfObjects; i++)
	{
		SAFEDEL(m_pSceneObjects[i]);
	}
	SAFEDELARR(m_pSceneObjects);

	for (int i = 0; i < m_uNumOfLights; i++)
	{
		SAFEDEL(m_pLights[i]);
	}
	SAFEDELARR(m_pLights);

	//SAFEDEL(m_pCharFactory);
	//SAFEDEL(m_pEnvFactory);
}