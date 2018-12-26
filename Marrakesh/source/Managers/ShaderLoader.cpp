#include "ShaderLoader.h"
#include "../Shaders/Shader.h"
#include "../../Util/include/JSON/json/json.h"

#include <string>
#include <cstdio>
#include <fstream>


ShaderLoader::ShaderLoader() :
	m_uNumShaders(0)
{
	m_shaders.resize(0);
}

ShaderLoader::~ShaderLoader()
{
	Release();
}


int ShaderLoader::LoadShaders(const char * filepath)
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

	const Json::Value& shaders = jobj["shaders"];
	m_uNumShaders = shaders.size();

	for (size_t i = 0; i < m_uNumShaders; i++)
	{
		SharedPtr<Shader> shader(new Shader());
		shader->Init(const_cast<char*>(shaders[i]["VS"].asCString()), const_cast<char*>(shaders[i]["FS"].asCString()));
		m_shaders.push_back(shader);
	}
	return 0;
}

SharedPtr<Shader> ShaderLoader::GetShaderById(unsigned short id)
{
	PASSERT((id < m_shaders.size()), "Requested shader ID is out of range!");

	if (id < m_shaders.size())
		return m_shaders[id];

	return nullptr;
}

void ShaderLoader::Release()
{
	m_shaders.resize(0);
}