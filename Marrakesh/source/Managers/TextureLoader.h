#pragma once

#include "../../Util/include/Singleton.h"
#include "../../Util/include/Defines.h"

class Texture;

class TextureLoader : public Singleton<TextureLoader>
{
public:

	TextureLoader();
	~TextureLoader();

	int						LoadTextures(const char * filepath);

	SharedPtr<Texture>		GetTextureById(unsigned short id, bool isCube = false);

	unsigned int			GetNum2dTexture() const { return m_uNum2dTextures; }
	unsigned int			GetNumCubeTexture() const { return m_uNumCubeTextures; }



private:

	unsigned int						m_uNum2dTextures;
	unsigned int						m_uNumCubeTextures;

	PArray<SharedPtr<Texture>>			m_textures2d;
	PArray<SharedPtr<Texture>>			m_texturesCube;

	void Release();
};