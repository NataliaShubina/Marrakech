#include "stdafx.h"
#include "IEffectManager.h"
#include "CEffect.h"
#include "CPass.h"
#include "CFbo.h"
#include "Globals.h"
#include "Vertex.h"
#include "CPostPShader.h"

#include <string>
#include <stdio.h>
#include <fstream>

#include "jsoncpp/json/json.h"

IEffectManager * IEffectManager::ms_pIntance = NULL;

int IEffectManager::LoadEffects(const char * path)
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
	const Json::Value& shaders = jobj["shaders"];
	m_uShadersNum = shaders.size();
	
	m_pEffectShaders = new CPostPShader*[m_uShadersNum];

	for (size_t i = 0; i < m_uShadersNum; i++)
	{
		m_pEffectShaders[i] = new CPostPShader();
		m_pEffectShaders[i]->Init(&shaders[i]["VS"].asString()[0], &shaders[i]["FS"].asString()[0]);
		m_pEffectShaders[i]->LocateParams();
	}

	//creating FBOs
	const Json::Value& jfbo = jobj["NoFBO"];
	m_uFrameBuffNum = jfbo.asUInt();

	m_pFbo = new CFbo *[m_uFrameBuffNum];
	for (size_t i = 0; i < m_uFrameBuffNum; i++)
	{
		m_pFbo[i] = new CFbo();
		m_pFbo[i]->Init();
	}

	//loasding effects
	const Json::Value& jeffects = jobj["effects"];
	m_uEffectsNum = jeffects.size();

	m_pEffect = new CEffect*[m_uEffectsNum];

	for (size_t i = 0; i < m_uEffectsNum; i++)
	{
		m_pEffect[i] = new CEffect();

		//loading passes
		unsigned short passesNum = jeffects[i]["passes"].size();
		CPass ** passes = new CPass*[passesNum];

		for (size_t j = 0; j < passesNum; j++)
		{
			passes[j] = new CPass();
			
			//loading texture array
			unsigned short texturesNum = jeffects[i]["passes"][j]["Textures"].size();
			char ** textures = new char *[texturesNum];

			for (size_t t = 0; t < texturesNum; t++)
			{
				textures[t] = new char[jeffects[i]["passes"][j]["Textures"][t].asString().length() + 1];
				strcpy(textures[t], jeffects[i]["passes"][j]["Textures"][t].asString().c_str());
			}

			//loading data array
			unsigned short dataVarNum = jeffects[i]["passes"][j]["OtherData"].size();
			float * data = new float[dataVarNum];

			for (size_t d = 0; d < dataVarNum; d++)
			{
				data[d] = jeffects[i]["passes"][j]["OtherData"][d].asFloat();
			}

			passes[j]->Load(
				jeffects[i]["passes"][j]["ShaderID"].asUInt(),	//shader id
				texturesNum,									//texture array size
				(const char**&)textures,										//texture array
				dataVarNum,										//data array size
				(const float*&)data,											//data array
				jeffects[i]["passes"][j]["Target"].asUInt()		// target buffer id
			);
		}
		m_pEffect[i]->SetPasses(passesNum, (const CPass **&)passes);
	}
	CreateScreeenMask();
	CreateSkyBoxTV();

	return 0;
}

void IEffectManager::CreateSkyBoxTV()
{
	
	Vertex vertices[4][4];

	//front face
	vertices[0][0].pos.x = -9.0f;	vertices[0][0].pos.y = 9.0f;	vertices[0][0].pos.z = -9.0f;
	vertices[0][1].pos.x = 9.0f;	vertices[0][1].pos.y = 9.0f;	vertices[0][1].pos.z = -9.0f;
	vertices[0][2].pos.x = 9.0f;	vertices[0][2].pos.y = -9.0f;	vertices[0][2].pos.z = -9.0f;
	vertices[0][3].pos.x = -9.0f;	vertices[0][3].pos.y = -9.0f;	vertices[0][3].pos.z = -9.0f;

	//back face
	vertices[1][0].pos.x = -9.0f;	vertices[1][0].pos.y = 9.0f;	vertices[1][0].pos.z = 9.0f;
	vertices[1][1].pos.x = 9.0f;	vertices[1][1].pos.y = 9.0f;	vertices[1][1].pos.z = 9.0f;
	vertices[1][2].pos.x = 9.0f;	vertices[1][2].pos.y = -9.0f;	vertices[1][2].pos.z = 9.0f;
	vertices[1][3].pos.x = -9.0f;	vertices[1][3].pos.y = -9.0f;	vertices[1][3].pos.z = 9.0f;

	//left face
	vertices[2][0].pos.x = -9.0f;	vertices[2][0].pos.y = 9.0f;	vertices[2][0].pos.z =  9.0f;
	vertices[2][1].pos.x = -9.0f;	vertices[2][1].pos.y = 9.0f;	vertices[2][1].pos.z = -9.0f;
	vertices[2][2].pos.x = -9.0f;	vertices[2][2].pos.y = -9.0f;	vertices[2][2].pos.z = -9.0f;
	vertices[2][3].pos.x = -9.0f;	vertices[2][3].pos.y = -9.0f;	vertices[2][3].pos.z =  9.0f;

	//right face
	vertices[3][0].pos.x = 9.0f;	vertices[3][0].pos.y = 9.0f;	vertices[3][0].pos.z = 9.0f;
	vertices[3][1].pos.x = 9.0f;	vertices[3][1].pos.y = 9.0f;	vertices[3][1].pos.z = -9.0f;
	vertices[3][2].pos.x = 9.0f;	vertices[3][2].pos.y = -9.0f;	vertices[3][2].pos.z = -9.0f;
	vertices[3][3].pos.x = 9.0f;	vertices[3][3].pos.y = -9.0f;	vertices[3][3].pos.z = 9.0f;

	for (int i = 0; i < 4; i++)
	{
		vertices[i][0].uv.x = 0.0f;	vertices[i][0].uv.y = 1.0f;
		vertices[i][1].uv.x = 1.0f;	vertices[i][1].uv.y = 1.0f;
		vertices[i][2].uv.x = 1.0f;	vertices[i][2].uv.y = 0.0f;
		vertices[i][3].uv.x = 0.0f;	vertices[i][3].uv.y = 0.0f;

		glGenBuffers(1, &m_skyMeshVboId[i]);
		glBindBuffer(GL_ARRAY_BUFFER, m_skyMeshVboId[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, &vertices[i][0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		unsigned short indices[6];
		indices[0] = 0; indices[1] = 1; indices[2] = 2;
		indices[3] = 2; indices[4] = 3; indices[5] = 0;

		glGenBuffers(1, &m_skyMeshIboId[i]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_skyMeshIboId[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void IEffectManager::CreateScreeenMask()
{
	Vertex vertices[4];

	vertices[0].pos.x = -1.0f;	vertices[0].pos.y = 1.0f;	vertices[0].pos.z = 0.0f;
	vertices[1].pos.x = 1.0f;	vertices[1].pos.y = 1.0f;	vertices[1].pos.z = 0.0f;
	vertices[2].pos.x = 1.0f;	vertices[2].pos.y = -1.0f;	vertices[2].pos.z = 0.0f;
	vertices[3].pos.x = -1.0f;	vertices[3].pos.y = -1.0f;	vertices[3].pos.z = 0.0f;

	vertices[0].uv.x = 0.0f;	vertices[0].uv.y = 1.0f;
	vertices[1].uv.x = 1.0f;	vertices[1].uv.y = 1.0f;
	vertices[2].uv.x = 1.0f;	vertices[2].uv.y = 0.0f;
	vertices[3].uv.x = 0.0f;	vertices[3].uv.y = 0.0f;

	glGenBuffers(1, &m_vboid);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	unsigned short indices[6];
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 2; indices[4] = 3; indices[5] = 0;

	glGenBuffers(1, &m_iboid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IEffectManager::Draw(unsigned short effectId)
{
	if (effectId > 0)
	{
		m_pEffect[effectId - 1]->Draw();
	}
}

void IEffectManager::DrawBox()
{
	for (int i = 0; i < 4; i++)
	{
		m_pEffectShaders[m_uShadersNum - 1]->DrawBox(i, (m_uFrameBuffNum - 4) + i);
	}
}

CPostPShader * IEffectManager::GetShaderById(unsigned short id) const
{
	if (m_pEffectShaders[id])
		return m_pEffectShaders[id];
	return nullptr;
}

CFbo * IEffectManager::GetFBOById(unsigned short id) const
{
	if (m_pFbo[id])
		return m_pFbo[id];
	return nullptr;
}

void IEffectManager::Release()
{

	if (m_pEffectShaders)
	{
		for (size_t i = 0; i < m_uShadersNum; i++)
		{
			SAFEDEL(m_pEffectShaders[i]);
		}
		SAFEDELARR(m_pEffectShaders);
	}

	if (m_pEffect)
	{
		for (size_t i = 0; i < m_uEffectsNum; i++)
		{
			SAFEDEL(m_pEffect[i]);
		}
		SAFEDELARR(m_pEffect);
	}
}