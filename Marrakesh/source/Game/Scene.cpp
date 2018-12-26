#include "Scene.h"

#include "Object.h"
#include "Grid.h"
#include "GridCell.h"

#include "../Shaders/Shader.h"
#include "../Entity/Mesh.h"
#include "../Entity/Texture.h"
#include "../Entity/Terrain.h"


#include "../Game/Camera.h"

#include "../../Util/include/JSON/json/json.h"

#include <stdio.h>
#include <fstream>

Scene::Scene():
	m_uNumObjects(0),
	m_uNumLights(0)
{
	m_objects.resize(0);
}

Scene::~Scene()
{
	m_objects.resize(0);
}

int Scene::Load(const char * filename)
{
	std::ifstream file(filename);

	PASSERT(file.is_open(), "Cannot open scene file");
	if (!file.is_open())
	{
		return -1;
	}

	Json::Value jobj;
	Json::Reader reader;

	bool parsingResult = reader.parse(file, jobj);

	PASSERT(parsingResult, "JSON cannot parse scene file");
	if (!parsingResult)
	{
		return -2;
	}

	////////////////////////////////////////////////////////////////       loading objects         ////////////////////////////////////////////////////////////////////////

	const Json::Value& objs = jobj["objects"];
	m_uNumObjects = objs.size();

	unsigned int * textureCubeIndices;
	unsigned int * texture2dIndices;
	for (size_t i = 0; i < m_uNumObjects; i++)
	{
		SharedPtr<Object> object(new Object());

		//loading models
		object->InitModel(objs[i]["model"].asInt());

		int dsize = objs[i]["2Dtex"].size();
		//loading 2d textures
		if (dsize > 0)
		{
			texture2dIndices = new unsigned int[dsize];
			for (auto j = 0; j < dsize; j++)
			{
				texture2dIndices[j] = objs[i]["2Dtex"][j].asUInt();
			}
			object->InitTextures2d(objs[i]["2Dtex"].size(), texture2dIndices);
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
			object->InitCubeTextures(objs[i]["cubeTex"].size(), textureCubeIndices);
			delete[] textureCubeIndices;
		}
		//loading shader
		object->InitShader(objs[i]["shader"].asUInt());

		Object::Parameters params;
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

		math::vec3 pos = math::vec3(objs[i]["position"][0].asFloat(), objs[i]["position"][1].asFloat(), objs[i]["position"][2].asFloat());
		math::vec3 rot = math::vec3(objs[i]["rotation"][0].asFloat(), objs[i]["rotation"][1].asFloat(), objs[i]["rotation"][2].asFloat());
		math::vec3 scale = math::vec3(objs[i]["scale"][0].asFloat(), objs[i]["scale"][1].asFloat(), objs[i]["scale"][2].asFloat());
		//loading moving param
		object->InitObjectParams(objs[i]["moving"].asCString(), //loading move tipe
			pos, //loading position
			rot, //loading rotation
			scale, //loading scale
			params); //loading params 

		if (objs[i]["color"])
		{
			math::vec3 color = math::vec3(objs[i]["color"][0].asFloat(), objs[i]["color"][1].asFloat(), objs[i]["color"][2].asFloat());
			object->SetColor(color);
		}

		m_objects.push_back(object);
	}

	////////////////////////////////////////////////////////////////       loading fog         ////////////////////////////////////////////////////////////////////////

	//const Json::Value& jfog = jobj["fog"];
	//m_fog.start = jfog["start"].asFloat();
	//m_fog.range = jfog["range"].asFloat();
	//m_fog.color = Vector3(jfog["color"][0].asFloat(), jfog["color"][1].asFloat(), jfog["color"][1].asFloat());

	////////////////////////////////////////////////////////////////       loading camera         ////////////////////////////////////////////////////////////////////////

	const Json::Value& cam = jobj["camera"];
	m_camera = std::make_shared<Camera>();
	math::vec3 pos = math::vec3(cam["position"][0].asFloat(), cam["position"][1].asFloat(), cam["position"][2].asFloat());
	m_camera->SetPosition(pos);
	m_camera->SetLook(math::vec3(0.0f, -0.5f, -0.5f));
	m_camera->SetWorldUp(math::vec3(0.0f, 1.0f, 0.0f));
	m_camera->SetSpeed(cam["speed"].asFloat(), cam["rot_speed"].asFloat());
	m_camera->SetVisibleArea(cam["fov"].asFloat(), cam["near"].asFloat(), cam["far"].asFloat());
	m_camera->SetRotAngle(1.0f);
	m_camera->ComputeMatrices();

	////////////////////////////////////////////////////////////////       loading lights         ////////////////////////////////////////////////////////////////////////

	/*const Json::Value& jamb = jobj["ambient_light"];
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
	}*/

	m_grid = std::make_shared<Grid>();
	m_grid->Init(std::make_shared<Scene>(*this));

	return 0;
}

void Scene::Draw()
{
	glEnable(GL_DEPTH_TEST);

	m_camera->ComputeMatrices();

	for (size_t i = 0; i < m_uNumObjects; i++)
	{
		m_objects[i]->Draw(m_camera.get());
	}

	glDisable(GL_DEPTH_TEST);
}

void Scene::Update(float deltaTime)
{

}