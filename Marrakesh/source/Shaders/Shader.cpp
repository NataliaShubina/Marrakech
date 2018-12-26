#include "Shader.h"

#include "../Entity/Texture.h"
#include "../Entity/Vertex.h"
#include "../../Util/include/Defines.h"
#include "../Utilities/utilities.h"

#include <fstream>
#include <string>

Shader::~Shader() 
{
	glDeleteProgram(m_program);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
}

int Shader::Init(char * fileVertexShader, char * fileFragmentShader)
{
	m_vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (m_vertexShader == 0)
		return -1;

	m_fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (m_fragmentShader == 0)
	{
		glDeleteShader(m_vertexShader);
		return -2;
	}

	m_program = esLoadProgram(m_vertexShader, m_fragmentShader);
	return 0;
}

void Shader::Use()
{
	glUseProgram(m_program);
}

void Shader::SetBool(const char * name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_program, name), (short)value);
}

void Shader::SetInt(const char * name, int value)	const
{
	glUniform1i(glGetUniformLocation(m_program, name), value);
}

void Shader::SetFloat(const char * name, float value) const
{
	glUniform1f(glGetUniformLocation(m_program, name), value);
}

void Shader::SetVertexAttributes()	const
{
	auto positionAttribute	= glGetAttribLocation(m_program, "a_posL");
	auto uvAttribute		= glGetAttribLocation(m_program, "a_uv");
	auto normAttribute		= glGetAttribLocation(m_program, "a_norm");

	GLfloat *ptr = (GLfloat*)0;

	if (positionAttribute != -1)
	{
		glEnableVertexAttribArray(positionAttribute);
		glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (normAttribute != -1)
	{
		glEnableVertexAttribArray(normAttribute);
		glVertexAttribPointer(normAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ptr + 3);
	}

	if (uvAttribute != -1)
	{
		glEnableVertexAttribArray(uvAttribute);
		glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ptr + 6);
	}
}

void Shader::SetTextures(const char * name, unsigned int size, const GLuint * value) const
{
	glUniform1iv(glGetUniformLocation(m_program, name), size, (GLint *)&value[0]);
}

void Shader::SetMatrix4x4F(const char * name, const math::Matrix& value) const
{
	auto mtxUniform = glGetUniformLocation(m_program, name);
	glUniformMatrix4fv(mtxUniform, 1, false, (GLfloat *)&value);
}
 
void Shader::Set3VectorF(const char * name, const math::vec3& value)	 const
{
	glUniform3fv(glGetUniformLocation(m_program, name), 1, (GLfloat *)&value);
}

void Shader::BindBuffers(GLuint vbo, GLuint ibo)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}