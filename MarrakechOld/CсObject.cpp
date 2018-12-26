#include "stdafx.h"
#include "CObject.h"
#include "CTexture.h"
//
//using objects::CObject;
//using objects::CFog;
//using objects::CTexture;
//
//CObject::CObject() :
//	m_vboid(0),
//	m_iboid(0),
//	m_pObjectShader(nullptr),
//	m_pObjectTexture(nullptr),
//	m_mtxLocalToWorld(0),
//	m_mtxScale(0),
//	m_position(0.0f, 0.0f, 0.0f)
//{
//
//}
//
//CObject::~CObject()
//{
//	glDeleteBuffers(1, &m_vboid);
//	glDeleteBuffers(1, &m_iboid);
//	SAFEDEL(m_pObjectShader);
//	if (m_uTextureCount > 1)
//	{
//		SAFEDELARR(m_pObjectTexture);
//	}
//	else
//	{
//		SAFEDEL(m_pObjectTexture);
//	}
//}
//
//
//void CObject::SetLocalToWorldMatrix(const Matrix& mtx)
//{
//	m_mtxLocalToWorld = mtx;
//}
//
//void CObject::SetPosition(const Vector3& position)
//{
//	m_position = position;
//}
//
//void CObject::SetPosition(float x, float y, float z)
//{
//	m_position = Vector3(x, y, z);
//}
//
//void CObject::SetScale(const Vector3& scaleVector)
//{
//	m_mtxScale.SetScale(scaleVector.x, scaleVector.y, scaleVector.z);
//}
//
//void CObject::SetScale(const Matrix& scaleMatrix)
//{
//	m_mtxScale = scaleMatrix;
//}
//
//void CObject::SetShaderPointer(CShaders * shader)
//{
//	m_pObjectShader = shader;
//}
//
//void CObject::SetTexturePointer(CTexture * texture)
//{
//	m_pObjectTexture = texture;
//}
//
//CFog::CFog() :
//	m_fogStart(0.0f),
//	m_fogRange(0.0f),
//	m_fogColor(0.0f, 0.0f, 0.0f)
//{
//
//}
//
//void CFog::InitFog(float fogStart, float fogRange, const Vector3 & fogColor)
//{
//	m_fogStart = fogStart;
//	m_fogRange = fogRange;
//	m_fogColor = fogColor;
//}
//
