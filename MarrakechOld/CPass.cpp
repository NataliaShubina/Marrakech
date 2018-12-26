#include "stdafx.h"
#include "CPass.h"
#include "IEffectManager.h"
#include "CFbo.h"
#include "CShaders.h"
#include "CPostPShader.h"
#include "Globals.h"
#include <memory>
#include <string>

CPass::CPass() :
	m_uShaderId(0),
	m_uTextureIdsNum(0),
	m_uDataVarNum(0),
	m_pTextureIds(nullptr),
	m_uFboId(0),
	m_pData(nullptr)
{

}

void CopySubstring(char * str1, char * str2, unsigned int length)
{
	while (length)
	{
		*str1++ = *str2++;
		--length;
	}
}

void CPass::Draw()
{
	if (m_uFboId)
	{
		IEffectManager::GetInstance()->GetFBOById(m_uFboId - 1)->BindFBO();
		IEffectManager::GetInstance()->GetShaderById(m_uShaderId)->Draw(this);
		IEffectManager::GetInstance()->GetFBOById(m_uFboId - 1)->UnbindFBO();
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		IEffectManager::GetInstance()->GetShaderById(m_uShaderId)->Draw(this);
	}
}

void CPass::Load(unsigned short shaderId, unsigned short textureNum, const char **& id, unsigned short dataNum, const float *& data, unsigned short fboId)
{
	m_uShaderId = shaderId;


	//get texture Ids
	m_uTextureIdsNum = textureNum;
	char ** textureIds = (char**)id;
	m_pTextureIds = new GLuint[m_uTextureIdsNum];

	for (size_t i = 0; i<m_uTextureIdsNum; i++)
	{
		const unsigned int size = strlen(textureIds[i]);
		const char type = textureIds[i][size - 1];
		switch (type)
		{
			char *cId;
		case 'c':

			cId = new char[size-1];
			CopySubstring(cId, textureIds[i], size-1);
			m_pTextureIds[i] = IEffectManager::GetInstance()->GetFBOById((unsigned short)atoi(cId) - 1)->GetColorTextureHandler();
			delete[] cId;
			cId = nullptr;
			break;

		case 'd':

			cId = new char[size-1];
			strncpy(cId, textureIds[i], size - 1);
			m_pTextureIds[i] = IEffectManager::GetInstance()->GetFBOById((unsigned short)atoi(cId) - 1)->GetDepthTextureHandler();
			delete[] cId;
			cId = nullptr;
			break;

		case '0':
			m_pTextureIds[i] = 0;
			break;

		default:
			m_pTextureIds[i] = 0;
			cId = nullptr;
			break;
		}
	}
	
	for (size_t i = 0; i < m_uTextureIdsNum; i++)
	{
		if (id[i])
			delete[] id[i];
	}
	delete[] id;

	m_uDataVarNum = dataNum;
	m_pData = (float *)data;

	m_uFboId = fboId;
}


CPass::~CPass()
{
	SAFEDELARR(m_pTextureIds);
	SAFEDELARR(m_pData);
}