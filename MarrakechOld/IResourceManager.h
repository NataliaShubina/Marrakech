#pragma once

class CModel;
class CShaders;
class CTexture;
class CCTerrain;


class IResourceManager
{
protected:
	IResourceManager() {}
	~IResourceManager() { Release(); }

	IResourceManager(const IResourceManager&) {}
	IResourceManager operator =(const IResourceManager&) {}

public:
	static IResourceManager * GetInstance()
	{
		if (ms_pIntance == nullptr)
			ms_pIntance = new IResourceManager;
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
	static IResourceManager * ms_pIntance;

public:

	int LoadEngineResources(const char * path);
	int GetTotalNumber() const { return m_uModelNum + m_uShadersNum + m_u2dTexturesNum + m_uCubeTextureNum + 1; }

	CModel ** GetModel() const { return m_pModels; }
	CModel * GetModelById(short modelId) const;

	CShaders ** GetShaders() const { return m_pShaders; }
	CShaders * GetShadersById(unsigned short shaderId) const;

	CTexture ** GetTextures2d() const { return m_pTextures2d; }
	CTexture * GetTextures2dById(unsigned short textureId) const;

	CTexture ** GetCubeTextures() const { return m_pTexturesCube; }
	CTexture * GetCubeTexturesById(unsigned short textureId) const;

	const unsigned int GetModelsNumber() const { return m_uModelNum; }
	const unsigned int GetShadersNumber() const { return m_uShadersNum; }
	const unsigned int GetTextures2dNumber() const { return m_u2dTexturesNum; }
	const unsigned int GetCubeTexturesNumber() const { return m_uCubeTextureNum; }

private:

	unsigned short m_uModelNum;
	CModel ** m_pModels;
	CCTerrain * m_pTerrain;
		
	unsigned short m_uShadersNum;
	CShaders ** m_pShaders;

	unsigned short m_u2dTexturesNum;
	CTexture ** m_pTextures2d;

	unsigned short m_uCubeTextureNum;
	CTexture ** m_pTexturesCube;

	void Release();
};
