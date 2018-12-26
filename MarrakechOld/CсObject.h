#pragma once
#include "../Utilities/utilities.h"

#ifndef SAFEDEL(p)
#define SAFEDEL(p) {if(p) delete p; p=nullptr;} 
#endif

#ifndef SAFEDELARR(p)
#define SAFEDELARR(p) {if(p) delete[] p; p=nullptr;} 
#endif

class CObject
{
public:
CObject();
	virtual ~CObject();

	//virtual const Matrix & GetLocalToWorldMatrix() const { return m_mtxLocalToWorld; }
	//virtual const Vector3 & GetPosition() const { return m_position; }
	//virtual const Matrix & GetScaleMatrix() const { return m_mtxScale; }
	//virtual CShaders * GetShadersPointer() const { return m_pObjectShader; }
	//virtual CTexture * GetTexturePointer() const { return m_pObjectTexture; }
	
	virtual int Init(const char * filePath, int textureCount, const Vector3 &  scaleVec) = 0;
	virtual void Draw(const CCamera& camera) = 0;
	virtual void Update(float deltatime) = 0;
	virtual void LoadTexture(const char * textureFile, ...) = 0;
	virtual bool LoadFromFile(const char * filePath) = 0;

	virtual void SetLocalToWorldMatrix(const Matrix& mtx);
	virtual void SetPosition(const Vector3& position);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetScale(const Vector3& scaleVector);
	virtual void SetScale(const Matrix& scaleMatrix);
	virtual void SetShaderPointer(CShaders * shader);
	virtual void SetTexturePointer(CTexture * texture);

protected:

	GLuint m_vboid;
	GLuint m_iboid;
};


class CFog
{
public:
	CFog();
	void InitFog(float fogStart, float fogRange, const Vector3 & fogColor);

	inline const float GetStartPosition() { return m_fogStart; }
	inline const float GetRange() { return m_fogRange; }
	inline const Vector3& GetColor() { return m_fogColor; }

private:
	float m_fogStart;
	float m_fogRange;
	Vector3 m_fogColor;	
};
