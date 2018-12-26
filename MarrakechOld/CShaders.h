#pragma once
#include "CBaseShader.h"

class CTexture;
class CObject;
class CCamera;
class CLight;
struct SFog;
struct SAmbientLight;

class CShaders: public CBaseShader
{
public:

	void LocateParams();
	void Draw(bool depthTest, const CObject * object, const CCamera * camera, unsigned short lightCount, const CLight ** light, const SAmbientLight& ambLight, const SFog& fog);

private:

	//vertex attributes
	GLint m_normAttribute;
	GLint m_binormAttribute;
	GLint m_tgtAttribute;

	//matrices
	GLint m_matrixMVP;
	GLint m_mtxWorld;
	GLint m_mtxView;


	//terrain shader attributes
	GLint m_tilingFactor;

	//fog attributes
	GLint m_fogColor;
	GLint m_fogStart;
	GLint m_fogRange;
	GLint m_camPosition;
	GLint m_specularPower;

	//light attributes
	GLint m_ambColor;
	GLint m_ambWeight;
	GLint m_depthColor;
	GLint m_depthDisp;


	//update attributes
	GLint m_time;
	GLint m_dMax;
	
};
