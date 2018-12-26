#pragma once
#include "../Utilities/utilities.h"

class CPostPShader;
class CFbo;
class CEffect;

class IEffectManager
{
protected:
	IEffectManager() {}
	~IEffectManager() { Release(); }

	IEffectManager(const IEffectManager&) {}
	IEffectManager operator =(const IEffectManager&) {}

public:
	static IEffectManager * GetInstance()
	{
		if (ms_pIntance == nullptr)
			ms_pIntance = new IEffectManager;
		return ms_pIntance;
	}
	static void DestroyInstance()
	{
		if (ms_pIntance)
		{
			delete ms_pIntance;
			ms_pIntance = 0;
		}
	}

protected:
	static IEffectManager * ms_pIntance;

public:

	int LoadEffects(const char * path);

	CPostPShader * GetShaderById(unsigned short id) const;
	CFbo * GetFBOById(unsigned short id) const;

	const GLuint GetVertexBufferID() const {return m_vboid;}
	const GLuint GetIndexBufferID() const {return m_iboid;}

	const GLuint GetFaceVertexBufferByID(int id) const { return m_skyMeshVboId[id]; }
	const GLuint GetFaceIndexBufferByID(int id) const { return m_skyMeshIboId[id]; }

	unsigned short GetFBONum() { return m_uFrameBuffNum; }

	void Draw(unsigned short effectId);
	void DrawBox();

private:

	unsigned short m_uShadersNum;
	unsigned short m_uFrameBuffNum;
	unsigned short m_uCubeFramebufferNum;
	unsigned short m_uEffectsNum;

	CPostPShader ** m_pEffectShaders;
	CFbo ** m_pFbo;
	CFbo ** m_pCubemapFbo;
	CEffect ** m_pEffect;

	GLuint m_vboid;
	GLuint m_iboid;

	GLuint m_skyMeshVboId[4];
	GLuint m_skyMeshIboId[4];

	void CreateScreeenMask();
	void CreateSkyBoxTV();
	void Release();

};