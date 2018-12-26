#pragma once
#include "SParameters.h"


class CModel;
class CTexture;
class CShaders;
class CCamera;
class CLight;
struct SFog;
struct SAmbientLight;

class CObject
{
public:

	CObject();
	~CObject();

	int InitModel(short modelId);
	int InitCubeTextures(unsigned short size, unsigned int * textureId);
	int InitTextures2d(unsigned short size, unsigned int * textureId);
	int InitShader(unsigned short shaderId);
	int InitObjectParams(const char * move, const Vector3& position, const Vector3& rotation, const Vector3& scale, const SParameters& params);

	CModel * GetModel() const { return m_pModel; };
	CShaders * GetShader() const { return m_pObjShader; };
	CTexture ** GetTextures2d() const{ return m_pTextures2d; }
	CTexture ** GetTexturesCube() const  { return m_pTexturesCube; }
	const Matrix& GetWorldMatrix() const { return m_mtxLocalToWorld;}

	float GetTilingFactor()  const { return m_Params.tiling_factor; }
	float GetSpecularPower() const { return m_Params.specular_power; }
	float GetDMax() const { return m_Params.dMax; }
	float GetDepthDispl() const { return m_Params.depth_displ; }

	const Vector3& GetColor() const { return m_color; }
	const Vector3& GetPosition() const { return m_position; }

	inline unsigned int GetTextureCount() const { return m_u2dTextureCount + m_uCubeTextureCount; }

	void SetColor(const Vector3& color);
	void SetPostition(const Vector3& position);

	inline unsigned int Get2dTextureCount() const {return m_u2dTextureCount;}
	inline unsigned int GetCubeTextureCount() const {return m_uCubeTextureCount;}

	void Draw(const CCamera * cameraView, unsigned short lightCount, const CLight ** light, const SAmbientLight& amblight, const SFog& fog);
	void Update(float deltatime);


private:
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;
	Matrix m_mtxLocalToWorld;

	CModel * m_pModel;

	unsigned int m_u2dTextureCount;
	unsigned int m_uCubeTextureCount;
	CTexture ** m_pTextures2d;
	CTexture ** m_pTexturesCube;

	CShaders * m_pObjShader;

	enum Move 
	{
		NO_MOVE,
		ROTATE
	}m_eMovement;

	SParameters m_Params;
	Vector3 m_color;
};
