#pragma once

#include "../../Util/include/Singleton.h"
#include "../../Util/include/Defines.h"

class Shader;

class ShaderLoader : public Singleton<ShaderLoader>
{
public:

	ShaderLoader();
	~ShaderLoader();

	int						LoadShaders(const char * filepath);
	SharedPtr<Shader>		GetShaderById(unsigned short id);
	int						GetShadersNum() const { return m_uNumShaders; }



private:
	unsigned int				m_uNumShaders;
	PArray<SharedPtr<Shader>>	m_shaders;

	void Release();
};