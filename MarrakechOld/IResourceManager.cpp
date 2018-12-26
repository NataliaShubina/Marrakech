#include "stdafx.h"
#include "IResourceManager.h"
#include "CModel.h"
#include "CTexture.h"
#include "CCTerrain.h"
#include "CShaders.h"
#include "Globals.h"

#include <string>
#include <stdio.h>
#include <fstream>

#include "jsoncpp/json/json.h"

IResourceManager * IResourceManager::ms_pIntance = NULL;

int IResourceManager::LoadEngineResources(const char * path)
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
	const Json::Value& models = jobj["models"];
	m_uModelNum = models.size();

	m_pModels = new  CModel*[m_uModelNum];

	for (size_t i = 0; i < m_uModelNum; i++)
	{
		m_pModels[i] = new CModel();
		m_pModels[i]->Init(models[i]["file"].asString().c_str());
		m_pModels[i]->BindBuffers();
	}

	const Json::Value& textures = jobj["2DTextures"];
	m_u2dTexturesNum = textures.size();

	m_pTextures2d = new CTexture *[m_u2dTexturesNum];

	for (size_t i = 0; i < m_u2dTexturesNum; i++)
	{
		m_pTextures2d[i] = new CTexture();
		if (!strcmp(textures[i]["tiling"].asString().c_str(), "REPEAT"))
		{
			m_pTextures2d[i]->Init(textures[i]["file"].asString().c_str(), CTexture::REPEAT);
		}
		else if (!strcmp(textures[i]["tiling"].asString().c_str(), "CLAMP_TO_EDGE"))
		{
			m_pTextures2d[i]->Init(textures[i]["file"].asString().c_str(), CTexture::CLAMP_TO_EDGE);
		}
	}

	const Json::Value& cubeTextures = jobj["cubeTextures"];
	m_uCubeTextureNum = cubeTextures.size();

	m_pTexturesCube = new CTexture *[m_uCubeTextureNum];

	for (size_t i = 0; i < m_uCubeTextureNum; i++)
	{
		m_pTexturesCube[i] = new CTexture();
		if (!strcmp(cubeTextures[i]["tiling"].asString().c_str(), "REPEAT"))
		{
			m_pTexturesCube[i]->InitCubeTexture(cubeTextures[i]["file"].asString().c_str(), CTexture::REPEAT);
		}
		else if (!strcmp(cubeTextures[i]["tiling"].asString().c_str(), "CLAMP_TO_EDGE"))
		{
			m_pTexturesCube[i]->InitCubeTexture(cubeTextures[i]["file"].asString().c_str(), CTexture::CLAMP_TO_EDGE);
		}
	}

	const Json::Value& shaders = jobj["shaders"];
	m_uShadersNum = shaders.size();

	m_pShaders = new  CShaders*[m_uShadersNum];

	for (size_t i = 0; i < m_uShadersNum; i++)
	{
		m_pShaders[i] = new CShaders();
		m_pShaders[i]->Init(&shaders[i]["VS"].asString()[0], &shaders[i]["FS"].asString()[0]);
	}
	
	const Json::Value& hMap = jobj["heightmap"];
	m_pTerrain = new CCTerrain();
	m_pTerrain->Init(hMap.asString().c_str());
	m_pTerrain->BindBuffers();

	return 0;
}

CModel * IResourceManager::GetModelById(short modelId) const
{
	if (modelId <= m_uModelNum)
	{
		if (modelId == -1)
		{
			return m_pTerrain;
		}
		return m_pModels[modelId];
	}
	return nullptr;
}

CShaders * IResourceManager::GetShadersById(unsigned short shaderId) const
{
	if (shaderId <= m_uShadersNum)
		return m_pShaders[shaderId];
	return nullptr;
}

CTexture * IResourceManager::GetTextures2dById(unsigned short textureId) const
{
	if (textureId <= m_u2dTexturesNum)
		return m_pTextures2d[textureId];
	return nullptr;
}

CTexture * IResourceManager::GetCubeTexturesById(unsigned short textureId) const
{
	if (textureId <= m_u2dTexturesNum)
		return m_pTexturesCube[textureId];
	return nullptr;
}

void IResourceManager::Release()
{
	for (int i = 0; i < m_uModelNum; i++)
	{
		SAFEDEL(m_pModels[i]);
	}
	SAFEDELARR(m_pModels);
	SAFEDEL(m_pTerrain);
	
	for (int i = 0; i < m_uShadersNum; i++)
	{
		SAFEDEL(m_pShaders[i]);
	}
	SAFEDELARR(m_pShaders);

	for (int i = 0; i < m_u2dTexturesNum; i++)
	{
		SAFEDEL(m_pTextures2d[i]);
	}
	SAFEDELARR(m_pTextures2d);

	for (int i = 0; i < m_uCubeTextureNum; i++)
	{
		SAFEDEL(m_pTexturesCube[i]);
	}
	SAFEDELARR(m_pTexturesCube);
}