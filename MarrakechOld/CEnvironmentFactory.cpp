#include "stdafx.h"

#include "CEnvironmentFactory.h"
#include "CObject.h"
#include "CShaders.h"
#include "jsoncpp/json/json.h"
#include <cmath>
#include <fstream>

int CEnvironmentFactory::LoadObjects(const char * filepath)
{
	std::ifstream file(filepath);

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

	const Json::Value& jchar = jobj["Environment"];
	m_uObjectNum = jchar.size();

	m_pSceneObjects = new CObject *[m_uObjectNum];

	const Json::Value& jcharPreset = jobj["EnvironmentPresets"];

	unsigned int * textureCubeIndices;
	unsigned int * texture2dIndices;
	for (size_t i = 0; i < m_uObjectNum; i++)
	{
		m_pSceneObjects[i] = new CObject();
		unsigned int set = jchar[i]["preset"].asUInt();

		//loading models
		m_pSceneObjects[i]->InitModel(jcharPreset[set]["model"].asInt());


		int dsize = jcharPreset[set]["2Dtex"].size();
		//loading 2d textures
		if (dsize > 0)
		{
			texture2dIndices = new unsigned int[dsize];
			for (size_t j = 0; j < dsize; j++)
			{
				texture2dIndices[j] = jcharPreset[set]["2Dtex"][j].asUInt();
			}
			m_pSceneObjects[i]->InitTextures2d(jcharPreset[set]["2Dtex"].size(), texture2dIndices);
			delete[] texture2dIndices;
		}

		int csize = jcharPreset[set]["cubeTex"].size();
		//loading Cube textures
		if (csize > 0)
		{
			textureCubeIndices = new unsigned int[csize];
			for (size_t j = 0; j < jcharPreset[set]["cubeTex"].size(); j++)
			{
				textureCubeIndices[j] = jcharPreset[set]["cubeTex"][j].asUInt();
			}
			m_pSceneObjects[i]->InitCubeTextures(jcharPreset[set]["cubeTex"].size(), textureCubeIndices);
			delete[] textureCubeIndices;
		}
		//loading shader
		m_pSceneObjects[i]->InitShader(jcharPreset[set]["shader"].asUInt());

		SParameters params;
		if (jcharPreset[set]["parameters"]["tiling_factor"])
		{
			params.tiling_factor = jcharPreset[set]["parameters"]["tiling_factor"].asFloat();
		}
		if (jcharPreset[set]["parameters"]["specular_power"])
		{
			params.specular_power = jcharPreset[set]["parameters"]["specular_power"].asFloat();
		}
		if (jcharPreset[set]["parameters"]["dMax"])
		{
			params.dMax = jcharPreset[set]["parameters"]["dMax"].asFloat();
		}
		if (jcharPreset[set]["parameters"]["depth_displ"])
		{
			params.depth_displ = jcharPreset[set]["parameters"]["depth_displ"].asFloat();
		}
		float x = static_cast<float> (rand()) / static_cast<float>(RAND_MAX / 1.0f);
		float y = static_cast<float> (rand()) / static_cast<float>(RAND_MAX / 1.0f);
		float z = static_cast<float> (rand()) / static_cast<float>(RAND_MAX / 1.0f);
		Vector3 pos = Vector3(x, y, z);

		x = static_cast<float> (rand()) / static_cast<float>(RAND_MAX / 1.0f);
		y = static_cast<float> (rand()) / static_cast<float>(RAND_MAX / 1.0f);
		z = static_cast<float> (rand()) / static_cast<float>(RAND_MAX / 1.0f);
		Vector3 rot = Vector3(x, y, z);

		float size = static_cast<float> (rand()) / static_cast<float>(RAND_MAX / 1.0f);
		Vector3 scale = Vector3(size, size, size);

		//loading moving param
		m_pSceneObjects[i]->InitObjectParams(jcharPreset[set]["moving"].asCString(), //loading move tipe
			pos, //loading position
			rot, //loading rotation
			scale, //loading scale
			params); //loading params 

		if (jcharPreset[i]["color"])
		{
			Vector3 color = Vector3(jcharPreset[i]["color"][0].asFloat(), jcharPreset[i]["color"][1].asFloat(), jcharPreset[i]["color"][2].asFloat());
			m_pSceneObjects[i]->SetColor(color);
		}

		m_pSceneObjects[i]->GetShader()->LocateParams();
	}
}