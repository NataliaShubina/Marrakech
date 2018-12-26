#include "stdafx.h"

#include "CCamera.h"
#include "ISceneManager.h"
#include "IEffectManager.h"
#include "CPass.h"
#include "CFbo.h"
#include "Vertex.h"
#include "CPostPShader.h"
#include "Globals.h"
#include "CCamera.h"
#include <cmath>

void CPostPShader::LocateParams()
{
	CBaseShader::LocateParams();
	m_blurStep = glGetUniformLocation(m_program, "u_step");
	m_bloomLimit = glGetUniformLocation(m_program, "u_limit");
	m_near = glGetUniformLocation(m_program, "u_near");
	m_far = glGetUniformLocation(m_program, "u_far");
	m_fade = glGetUniformLocation(m_program, "u_fade");
	m_clarity = glGetUniformLocation(m_program, "u_clarity");
	m_afterDOF = glGetUniformLocation(m_program, "u_afterDOF");
	m_height = glGetUniformLocation(m_program, "u_height");
	m_width = glGetUniformLocation(m_program, "u_width");
}


void CPostPShader::Draw(CPass * pass)
{
	glUseProgram(m_program);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, IEffectManager::GetInstance()->GetVertexBufferID());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IEffectManager::GetInstance()->GetIndexBufferID());


	GLfloat * ptr = (GLfloat*)0;

	if (this->m_positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_positionAttribute);
		glVertexAttribPointer(m_positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (this->m_uvAttribute != -1)
	{
		glEnableVertexAttribArray(m_uvAttribute);
		glVertexAttribPointer(m_uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ptr + 12);
	}

	int textureUnit = 0;
	if (pass)
	{
		GLuint * handlers = new GLuint[pass->GetTextureCount()];
		for (size_t i = 0; i < pass->GetTextureCount(); i++)
		{
			if (pass->GetTextureIDs()[i])
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, (GLuint)pass->GetTextureIDs()[i]);
				handlers[i] = i;
				textureUnit++;
			}
		}
		glUniform1iv(glGetUniformLocation(m_program, "u_textures2d"), textureUnit, (GLint *)&handlers[0]);
		SAFEDELARR(handlers);
	}

	if (m_blurStep != -1)
	{
		float x = 1.0f / Globals::screenWidth;
		float y = 1.0f / Globals::screenHeight;
		float z = sqrt(2.0f) / 2.0f * x;
		float w = sqrt(2.0f) / 2.0f * y;
		glUniform4f(m_blurStep, pass->GetData()[0] * x, pass->GetData()[0] * y, pass->GetData()[0] * z, pass->GetData()[0] * w);
	}

	if (m_bloomLimit != -1)
	{
		glUniform1f(m_bloomLimit, pass->GetData()[0]);
	}

	if (m_near != -1)
	{
		glUniform1f(m_near, ISceneManager::GetInstance()->GetCamera()->GetNearZ());
	}

	if (m_far != -1)
	{
		glUniform1f(m_far, ISceneManager::GetInstance()->GetCamera()->GetFarZ());
	}

	if (m_fade != -1)
	{
		glUniform1f(m_fade, pass->GetData()[1]);
	}

	if (m_clarity != -1)
	{
		glUniform1f(m_clarity, pass->GetData()[2]);
	}	

	if (m_height != -1)
	{
		float h = 1.0f / Globals::screenHeight;
		glUniform1f(m_height, h);
	}

	if (m_width != -1)
	{
		float w = 1.0f / Globals::screenWidth;
		glUniform1f(m_width, w);
	}

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void CPostPShader::DrawBox(int index, unsigned short sourceId)
{
	glUseProgram(m_program);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, IEffectManager::GetInstance()->GetFaceVertexBufferByID(index));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IEffectManager::GetInstance()->GetFaceIndexBufferByID(index));

	GLfloat * ptr = (GLfloat*)0;

	if (this->m_positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_positionAttribute);
		glVertexAttribPointer(m_positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (this->m_uvAttribute != -1)
	{
		glEnableVertexAttribArray(m_uvAttribute);
		glVertexAttribPointer(m_uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ptr + 12);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, IEffectManager::GetInstance()->GetFBOById(sourceId)->GetColorTextureHandler());
	glUniform1i(glGetUniformLocation(m_program, "u_textures2d"), 0);

	glUniformMatrix4fv(glGetUniformLocation(m_program, "u_mtxMVP"), 1, false, (GLfloat *)&ISceneManager::GetInstance()->GetCamera()->GetResultMatrix());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisable(GL_DEPTH_TEST);
}