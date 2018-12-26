#include "stdafx.h"
#include "CShaders.h"
#include "CTexture.h"
#include "CModel.h"
#include "CObject.h"
#include "CCamera.h"
#include "SFog.h"
#include "SAmbientLight.h"
#include "CLight.h"
#include "Globals.h"

#include "IEffectManager.h"
#include "CFbo.h"

#include <string>

void CShaders::LocateParams()
{
	CBaseShader::LocateParams();

	//locate vertex attribs
	m_normAttribute = glGetAttribLocation(m_program, "a_norm");
	m_binormAttribute = glGetAttribLocation(m_program, "a_binorm");
	m_tgtAttribute = glGetAttribLocation(m_program, "a_tgt");


	//locate matrices
	m_matrixMVP = glGetUniformLocation(m_program, "u_mtxMVP");
	m_mtxWorld = glGetUniformLocation(m_program, "u_mtxToWorld");
	m_mtxView = glGetUniformLocation(m_program, "u_mtxView");

	//locate  tiling factor
	m_tilingFactor = glGetUniformLocation(m_program, "a_tFactor");

	//locate fog params
	m_fogColor = glGetUniformLocation(m_program, "u_fogColor");
	m_fogStart = glGetUniformLocation(m_program, "u_fogStart");
	m_fogRange = glGetUniformLocation(m_program, "u_fogRange");
	m_camPosition = glGetUniformLocation(m_program, "u_camPosition");

	//locate ambient light
	m_time = glGetUniformLocation(m_program, "u_Time");
	m_dMax = glGetUniformLocation(m_program, "u_dMax");

	//object params

	m_depthColor = glGetUniformLocation(m_program, "u_depthColor");
	m_depthDisp = glGetUniformLocation(m_program, "u_depthDisp");
	
	m_ambColor = glGetUniformLocation(m_program, "u_ambColor");
	m_ambWeight = glGetUniformLocation(m_program, "u_ambWeight");
	m_specularPower = glGetUniformLocation(m_program, "u_specularPower");
}


void CShaders::Draw(bool depthTest, const CObject * object, const CCamera * camera, unsigned short lightCount, const CLight ** light, const SAmbientLight& ambLight, const SFog& fog)
{
	glUseProgram(m_program);

	glBindBuffer(GL_ARRAY_BUFFER, object->GetModel()->GetVertBufferId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->GetModel()->GetIndexBufferId());
	

	////////////////////////////////////////////////////////////////       textures       ////////////////////////////////////////////////////////////////////////

	
	int textureUnit = 0;
	if (object->GetTextures2d())
	{
		GLuint * texture2dHadlers = new GLuint[object->Get2dTextureCount()];

		for (int i = 0; i < object->Get2dTextureCount(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(GL_TEXTURE_2D, object->GetTextures2d()[i]->GetHandler());
			texture2dHadlers[i] = textureUnit;
			textureUnit++;
		}
		glUniform1iv(glGetUniformLocation(m_program, "u_textures2d"), object->Get2dTextureCount(), (GLint *)&texture2dHadlers[0]);
		SAFEDELARR(texture2dHadlers);
	}

	if (object->GetTexturesCube())
	{
		GLuint * textureCubeHadlers = new GLuint[object->GetCubeTextureCount()];
		for (int i = 0; i < object->GetCubeTextureCount(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(GL_TEXTURE_CUBE_MAP, object->GetTexturesCube()[i]->GetHandler());
			textureCubeHadlers[i] = textureUnit;
			textureUnit++;
		}

		glUniform1iv(glGetUniformLocation(m_program, "u_texturesCube"), object->GetCubeTextureCount(), (GLint *)&textureCubeHadlers[0]);
		SAFEDELARR(textureCubeHadlers);
	}



	////////////////////////////////////////////////////////////////       vertex params        ////////////////////////////////////////////////////////////////////////

	GLfloat *ptr = (GLfloat*)0;

	if (m_positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_positionAttribute);
		glVertexAttribPointer(m_positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (m_normAttribute != -1)
	{
		glEnableVertexAttribArray(m_normAttribute);
		glVertexAttribPointer(m_normAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ptr + 3);
	}

	if (m_binormAttribute != -1)
	{
		glEnableVertexAttribArray(m_binormAttribute);
		glVertexAttribPointer(m_binormAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ptr + 6);
	}

	if (m_tgtAttribute != -1)
	{
		glEnableVertexAttribArray(m_tgtAttribute);
		glVertexAttribPointer(m_tgtAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ptr + 9);
	}

	if (m_uvAttribute != -1)
	{
		glEnableVertexAttribArray(m_uvAttribute);
		glVertexAttribPointer(m_uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ptr + 12);
	}

	////////////////////////////////////////////////////////////////       object params        ////////////////////////////////////////////////////////////////////////

	Matrix MVP = (Matrix)object->GetWorldMatrix() * (Matrix)camera->GetResultMatrix();

	if (m_mtxWorld != -1)
		glUniformMatrix4fv(m_mtxWorld, 1, false, (GLfloat*)& object->GetWorldMatrix());

	if (m_matrixMVP != -1)
		glUniformMatrix4fv(m_matrixMVP, 1, false, (GLfloat*)&MVP);

	if(m_mtxView != -1)
		glUniformMatrix4fv(m_matrixMVP, 1, false, (GLfloat*)&camera->GetViewMatrix());

	if (m_tilingFactor != -1)
		glUniform1f(m_tilingFactor, object->GetTilingFactor());

	if (m_depthColor != -1)
		glUniform3fv(m_depthColor, 1, (GLfloat *)&object->GetColor());

	if (m_depthDisp != -1)
		glUniform1f(m_depthDisp, object->GetDepthDispl());


	if (m_time != -1)
		glUniform1f(m_time, Globals::m_time);

	if (m_dMax != -1)
	{
		glUniform1f(m_dMax, object->GetDMax());
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	////////////////////////////////////////////////////////////////       fog params        ////////////////////////////////////////////////////////////////////////

	if (m_fogStart != -1)
		glUniform1f(m_fogStart, fog.start);

	if (m_fogRange != -1)
		glUniform1f(m_fogRange, fog.range);

	if (m_fogColor != -1)
		glUniform3fv(m_fogColor, 1, (GLfloat *)&fog.color);

	if (m_camPosition != -1)
		glUniform3fv(m_camPosition, 1, (GLfloat*)&camera->GetPosition());


	////////////////////////////////////////////////////////////////       light params        ////////////////////////////////////////////////////////////////////////
	
	if (m_ambColor != -1)
		glUniform3fv(m_ambColor, 1, (GLfloat*)&ambLight.m_color);

	if (m_ambWeight != -1)
		glUniform1f(m_ambWeight, ambLight.m_weight);

	if (m_specularPower != -1)
		glUniform1f(m_specularPower, object->GetSpecularPower());


	Vector3 * colorArray = new Vector3[lightCount];
	Vector3 * positionArray = new Vector3[lightCount];

	for(size_t i = 0; i < lightCount; i++)
	{
		colorArray[i] = light[i]->GetColor();
		positionArray[i] = light[i]->GetPosition();	
	}

	glUniform3fv(glGetUniformLocation(m_program, "u_lightColor"), lightCount, (GLfloat *)&colorArray[0]);
	glUniform3fv(glGetUniformLocation(m_program, "u_lightPositions"), lightCount, (GLfloat *)&positionArray[0]);

	object->GetModel()->Draw();
	
	SAFEDELARR(colorArray);
	SAFEDELARR(positionArray);
}