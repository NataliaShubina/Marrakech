#pragma once

#include "../../Util/Math.h"
#include "../../Util/include/Defines.h"

class Mesh;
class Texture;
class Camera;
class Shader;
class Light;
struct Fog;
struct AmbientLight;

class Object
{

public:

	struct Parameters
	{
		float tiling_factor;
		float specular_power;
		float dMax;
		float depth_displ;
	};

	enum Move
	{
		NO_MOVE,
		ROTATE
	};

	Object();
	~Object();

	int InitModel(short modelId);
	int InitCubeTextures(unsigned short size, unsigned int * textureId);
	int InitTextures2d(unsigned short size, unsigned int * textureId);
	int InitShader(unsigned short shaderId);
	int InitObjectParams(const char * move, const math::vec3& position, const math::vec3& rotation, const math::vec3& scale, const Parameters& params);

	SharedPtr<Mesh>					GetModel()			const { return m_mesh; };
	SharedPtr<Shader>				GetShader()			const { return m_shader; };
	PArray<SharedPtr<Texture>>		GetTextures2d()		const { return m_textures2d; }
	PArray<SharedPtr<Texture>>		GetTexturesCube()	const { return m_texturesCube; }
	const math::Matrix&				GetWorldMatrix()	const { return m_mtxLocalToWorld; }

	float GetTilingFactor()		const { return m_Params.tiling_factor; }
	float GetSpecularPower()	const { return m_Params.specular_power; }
	float GetDMax()				const { return m_Params.dMax; }
	float GetDepthDispl()		const { return m_Params.depth_displ; }

	const math::vec3& GetColor()	const { return m_color; }
	const math::vec3& GetPosition() const { return m_position; }

	inline unsigned int GetTextureCount() const { return m_u2dTextureCount + m_uCubeTextureCount; }

	void SetColor(const math::vec3& color);
	void SetPostition(const math::vec3& position);

	inline unsigned int Get2dTextureCount()		const { return m_u2dTextureCount; }
	inline unsigned int GetCubeTextureCount()	const { return m_uCubeTextureCount; }

	void Draw(Camera * cameraView/*, unsigned short lightCount, const PArray<SharedPtr<Light>>& light, const AmbientLight& amblight, const Fog& fog*/);
	void Update(float deltatime);

private:
	math::vec3		m_position;
	math::vec3		m_rotation;
	math::vec3		m_scale;
	math::Matrix	m_mtxLocalToWorld;

	unsigned int					m_u2dTextureCount;
	unsigned int					m_uCubeTextureCount;
	
	SharedPtr<Mesh>					m_mesh;
	SharedPtr<Shader>				m_shader;
	PArray<SharedPtr<Texture>>		m_textures2d;
	PArray<SharedPtr<Texture>>		m_texturesCube;

	Move		m_eMovement;

	Parameters	m_Params;
	math::vec3	m_color;
};