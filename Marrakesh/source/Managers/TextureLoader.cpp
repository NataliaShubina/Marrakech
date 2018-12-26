#include "TextureLoader.h"
#include "../Entity/Texture.h"
#include "../../Util/include/JSON/json/json.h"

#include <string>
#include <cstdio>
#include <fstream>

TextureLoader::TextureLoader() :
	m_uNum2dTextures(0),
	m_uNumCubeTextures(0)
{
	m_textures2d.resize(0);
	m_texturesCube.resize(0);
}

TextureLoader::~TextureLoader()
{
	Release();
}


int TextureLoader::LoadTextures(const char * filepath)
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

	const Json::Value& textures = jobj["2DTextures"];
	m_uNum2dTextures = textures.size();

	for (auto i = 0; i < m_uNum2dTextures; i++)
	{
		SharedPtr<Texture> texture2d(new Texture());
		if (!strcmp(textures[i]["tiling"].asString().c_str(), "REPEAT"))
		{
			texture2d->Init(textures[i]["file"].asString().c_str(), Texture::REPEAT);
		}
		else if (!strcmp(textures[i]["tiling"].asString().c_str(), "CLAMP_TO_EDGE"))
		{
			texture2d->Init(textures[i]["file"].asString().c_str(), Texture::CLAMP_TO_EDGE);
		}
		m_textures2d.push_back(texture2d);
	}

	const Json::Value& cubeTextures = jobj["cubeTextures"];
	m_uNumCubeTextures = cubeTextures.size();

	for (auto i = 0; i < m_uNumCubeTextures; i++)
	{
		SharedPtr<Texture> textureCube(new Texture());
		if (!strcmp(cubeTextures[i]["tiling"].asString().c_str(), "REPEAT"))
		{
			textureCube->InitCubeTexture(cubeTextures[i]["file"].asString().c_str(), Texture::REPEAT);
		}
		else if (!strcmp(cubeTextures[i]["tiling"].asString().c_str(), "CLAMP_TO_EDGE"))
		{
			textureCube->InitCubeTexture(cubeTextures[i]["file"].asString().c_str(), Texture::CLAMP_TO_EDGE);
		}
		m_texturesCube.push_back(textureCube);
	}

	return 0;
}

SharedPtr<Texture> TextureLoader::GetTextureById(unsigned short id, bool isCube)
{
	if (!isCube)
	{
		PASSERT((id < m_textures2d.size()), "Requested texture ID is out of range!");

		if (id < m_textures2d.size())
			return m_textures2d[id];
		return nullptr;
	}
	else
	{
		PASSERT((id < m_texturesCube.size()), "Requested texture ID is out of range!");

		if (id < m_texturesCube.size())
			return m_texturesCube[id];
		return nullptr;
	}
	return nullptr;
}

void TextureLoader::Release()
{
	m_textures2d.resize(0);
	m_texturesCube.resize(0);
}