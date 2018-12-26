#include "Object.h"
#include "../Entity/Mesh.h"
#include "../Entity/Terrain.h"
#include "../Entity/Texture.h"
#include "../Shaders/Shader.h"
#include "../Managers/MeshLoader.h"
#include "../Managers/TextureLoader.h"
#include "../Managers/ShaderLoader.h"
#include "../Managers/TimeManager.h"
#include "../Game/Camera.h"

Object::Object() :
	m_position(0.0f, 0.0f, 0.0f),
	m_rotation(0.0f, 0.0f, 0.0f),
	m_scale(0.0f, 0.0f, 0.0f),
	m_mtxLocalToWorld(0),
	m_mesh(nullptr),
	m_shader(nullptr),
	m_u2dTextureCount(0),
	m_uCubeTextureCount(0),
	m_color(0.0f, 0.0f, 0.0f)
{
	m_mtxLocalToWorld.SetIdentity();
	m_textures2d.resize(0);
	m_texturesCube.resize(0);
}

Object::~Object()
{
	m_mesh = nullptr;
	m_shader = nullptr;

	m_textures2d.resize(0);
	m_texturesCube.resize(0);
}

void Object::SetPostition(const math::vec3& position)
{
	m_position = position;
	math::Matrix mtxTrans, mtxRotate, mtxScale;
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

int Object::InitModel(short modelId)
{
	if(modelId == -1)
		m_mesh = std::static_pointer_cast<Mesh>(MeshLoader::GetInstance()->GetTerrain());
	else
		m_mesh = MeshLoader::GetInstance()->GetMeshById(modelId);
	if (!m_mesh)
		return -1;
	return 0;
}

int Object::InitCubeTextures(unsigned short size, unsigned int * textureId)
{
	if (size == 0)
		return -1;

	m_uCubeTextureCount = size;
	for (size_t i = 0; i < size; i++)
	{
		m_texturesCube.push_back(TextureLoader::GetInstance()->GetTextureById(textureId[i], true));
	}

	return 0;
}

int Object::InitTextures2d(unsigned short size, unsigned int * textureId)
{
	if (size == 0)
		return -1;

	m_u2dTextureCount = size;
	for (size_t i = 0; i < size; i++)
	{
		m_textures2d.push_back(TextureLoader::GetInstance()->GetTextureById(textureId[i]));
	}

	return 0;
}

int Object::InitShader(unsigned short shaderId)
{
	m_shader = ShaderLoader::GetInstance()->GetShaderById(shaderId);
	if (m_shader)
		return 0;
	return -1;
}

int Object::InitObjectParams(const char * move, const math::vec3& position, const math::vec3& rotation, const math::vec3& scale, const Parameters& params)
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

	math::Matrix mtxTrans, mtxRotate, mtxScale;
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

void Object::Draw(Camera * cameraView/*, unsigned short lightCount, const PArray<SharedPtr<Light>>& light, const AmbientLight& amblight, const Fog& fog*/)
{
	m_shader->Use();
	m_shader->BindBuffers(m_mesh->GetVerttexBuffer(), m_mesh->GetIndexBuffer());

	int textureUnit = 0;
	if (m_u2dTextureCount)
	{
		GLuint * texture2dHadlers = new GLuint[m_u2dTextureCount];

		for (auto i = 0; i < m_u2dTextureCount; i++)
		{
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(GL_TEXTURE_2D, m_textures2d[i]->GetHandler());
			texture2dHadlers[i] = textureUnit;
			textureUnit++;
		}
		m_shader->SetTextures("u_textures2d", m_u2dTextureCount, texture2dHadlers);
		
		delete[] texture2dHadlers;
	}
	
	textureUnit = 0;
	if (m_uCubeTextureCount)
	{
		GLuint * textureCubeHadlers = new GLuint[m_uCubeTextureCount];
		for (auto i = 0; i < m_uCubeTextureCount; i++)
		{
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(GL_TEXTURE_CUBE_MAP,m_texturesCube[i]->GetHandler());
			textureCubeHadlers[i] = textureUnit;
			textureUnit++;
		}
		m_shader->SetTextures("u_texturesCube", m_uCubeTextureCount, textureCubeHadlers);
		
		delete[] textureCubeHadlers;
	}

	m_shader->SetVertexAttributes();

	math::Matrix MVP = (math::Matrix)m_mtxLocalToWorld * (math::Matrix)cameraView->GetResultMatrix();
	m_shader->SetMatrix4x4F("mtxMVP", MVP);
	//m_shader->SetMatrix4x4F("mtxWorld", GetWorldMatrix());
	//m_shader->SetMatrix4x4F("mtxView", camera->GetViewMatrix());

	m_shader->SetFloat("tiling", GetTilingFactor());
	//m_shader->Set3VectorF("depthColor", GetColor());
	//m_shader->SetFloat("depthDisp", GetDepthDispl());
	//m_shader->SetFloat("time", TimeManager::GetInstance()->GetTime());

	//if (m_Params.dMax)
	//{
	//	m_shader->SetFloat("dMax", GetDMax());
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//}

	m_mesh->Draw();
}

void Object::SetColor(const math::vec3& color)
{
	m_color = color;
}

void Object::Update(float deltatime)
{

}