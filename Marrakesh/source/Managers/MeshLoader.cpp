#include "MeshLoader.h"
#include "../Entity/Mesh.h"
#include "../Entity/Terrain.h"
#include "../../Util/include/JSON/json/json.h"

#include <string>
#include <cstdio>
#include <fstream>


MeshLoader::MeshLoader() :
	m_uNumModel(0)
{
	m_models.resize(0);
}

MeshLoader::~MeshLoader()
{
	Release();
}

int MeshLoader::LoadMeshes(const char * filepath)
{
	std::ifstream file(filepath);

	PASSERT(file.is_open(), "Cannot open scene file!");
	if (!file.is_open())
		return -1;

	Json::Value jobj;
	Json::Reader reader;

	bool parsingResult = reader.parse(file, jobj);

	PASSERT(parsingResult, "Cannot parse JSON file!");
	if (!parsingResult)
	{
		return -2;
	}

	const Json::Value& models = jobj["models"];
	m_uNumModel = models.size();

	for (auto i = 0; i < m_uNumModel; i++)
	{
		SharedPtr<Mesh> model(new Mesh());
		auto filename = models[i]["file"].asCString();

		if (strstr(filename, ".tga")!= 0)
		{
			m_terrain = std::make_shared<Terrain>();
			m_terrain->Load(filename);
			m_terrain->BindBuffers();
		}
		else
		{
			model->Load(filename);
			model->BindBuffers();
			m_models.push_back(model);
		}
	}
	return 0;
}

SharedPtr<Mesh> MeshLoader::GetMeshById(unsigned short id)
{
	PASSERT((id < m_models.size()), "Requested mesh ID is out of range!");
	
	if (id < m_models.size())
		return m_models[id];

	return nullptr;
}

void MeshLoader::Release()
{
	m_models.resize(0);
}