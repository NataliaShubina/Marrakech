#include "stdafx.h"
#include "CObject.h"
#include "CTexture.h"
#include "CCTerrain.h"
#include "SFog.h"
#include "SAmbientLight.h"
#include "CShaders.h"
#include "CLight.h"
#include "IResourceManager.h"
#include "Globals.h"

#include <cstring>



CObject::CObject() :
	m_position(0.0f, 0.0f, 0.0f),
	m_rotation(0.0f, 0.0f, 0.0f),
	m_scale(0.0f, 0.0f, 0.0f),
	m_mtxLocalToWorld(0),
	m_pModel(nullptr),
	m_pTextures2d(nullptr),
	m_pTexturesCube(nullptr),
	m_pObjShader(nullptr),
	m_u2dTextureCount(0),
	m_uCubeTextureCount(0),
	m_color(0.0f, 0.0f, 0.0f)
{
	m_mtxLocalToWorld.SetIdentity();
}

CObject::~CObject()
{
	m_pModel = nullptr;
	if (m_pTextures2d)
	{
		for (size_t i = 0; i < m_u2dTextureCount; i++)
		{
			m_pTextures2d = nullptr;
		}
		delete[] m_pTextures2d;
	}

	if (m_pTexturesCube)
	{
		for (size_t i = 0; i < m_uCubeTextureCount; i++)
		{
			m_pTexturesCube = nullptr;
		}
		delete[] m_pTexturesCube;
	}
	m_pObjShader = nullptr;
}

void CObject::SetPostition(const Vector3& position)
{
	m_position = position;
	Matrix mtxTrans, mtxRotate, mtxScale;
	mtxTrans.SetIdentity();
	mtxRotate.SetIdentity();
	mtxScale.SetIdentity();
	m_mtxLocalToWorld = mtxTrans.SetTranslation(m_position.x, m_position.y, m_position.z);

	mtxRotate.SetRotationX(m_rotation.x);
	mtxRotate.SetRotationY(m_rotation.y);
	mtxRotate.SetRotationZ(m_rotation.z);
	mtxScale.SetScale(m_scale.x, m_scale.y, m_scale.z);
	m_mtxLocalToWorld = mtxScale * mtxTrans * mtxRotate;

}

int CObject::InitModel(short modelId)
{
	m_pModel = IResourceManager::GetInstance()->GetModelById(modelId);
	if (!m_pModel)
		return -1;
	return 0;
}

int CObject::InitCubeTextures(unsigned short size, unsigned int * textureId)
{
	if (size == 0)
		return -2;

	m_uCubeTextureCount = size;
	m_pTexturesCube = new CTexture *[m_uCubeTextureCount];
	for (size_t i = 0; i < size; i++)
	{
		m_pTexturesCube[i] = IResourceManager::GetInstance()->GetCubeTexturesById(textureId[i]);
	}
	if(m_pTexturesCube)
		return 0;
	return -1;
}

int CObject::InitTextures2d(unsigned short size, unsigned int * textureId)
{
	if (size == 0)
		return -2;

	m_u2dTextureCount = size;
	m_pTextures2d = new CTexture *[m_u2dTextureCount];
	for (size_t i = 0; i < size; i++)
	{
		m_pTextures2d[i] = IResourceManager::GetInstance()->GetTextures2dById(textureId[i]);
	}
	if (m_pTextures2d)
		return 0;
	return -1;
}

int CObject::InitShader(unsigned short shaderId)
{
	m_pObjShader = IResourceManager::GetInstance()->GetShadersById(shaderId);
	if (m_pObjShader)
		return 0;
	return -2;
}

int CObject::InitObjectParams(const char * move, const Vector3& position, const Vector3& rotation, const Vector3& scale, const SParameters& params)
{
	if (!strcmp("no_move", move))
	{
		m_eMovement = NO_MOVE;
	}
	else if (!strcmp("rotate", move))
	{
		m_eMovement = ROTATE;
	}

	m_position = position;
	m_rotation = rotation;
	m_scale = scale;

	Matrix mtxTrans, mtxRotate, mtxScale;
	mtxTrans.SetIdentity();
	mtxRotate.SetIdentity();
	mtxScale.SetIdentity();
	m_mtxLocalToWorld = mtxTrans.SetTranslation(m_position.x, m_position.y, m_position.z);
	mtxRotate.SetRotationX(m_rotation.x);
	mtxRotate.SetRotationY(m_rotation.y);
	mtxRotate.SetRotationZ(m_rotation.z);
	mtxScale.SetScale(m_scale.x, m_scale.y, m_scale.z);
	m_mtxLocalToWorld = mtxScale * mtxTrans * mtxRotate;
	m_Params = params;

	return 0;
}

void CObject::Draw(const CCamera * cameraView, unsigned short lightCount, const CLight ** light, const SAmbientLight& amblight,  const SFog& fog)
{
	m_pObjShader->Draw(true, this, cameraView, lightCount, light, amblight, fog);
}

void CObject::SetColor(const Vector3& color)
{
	m_color = color;
}

void CObject::Update(float deltatime)
{
	Matrix mtxTrans, mtxRotate, mtxScale;
	switch (m_eMovement)
	{
	case ROTATE:
		m_mtxLocalToWorld = (Matrix().SetIdentity().SetRotationY(deltatime)) * m_mtxLocalToWorld;
		break;
	default:
		break;
	}
}