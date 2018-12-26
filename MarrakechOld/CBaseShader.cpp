#include "stdafx.h"
#include "CBaseShader.h"

int CBaseShader::Init(char * fileVertexShader, char * fileFragmentShader)
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

	strcpy(m_fileVS, fileVertexShader);
	strcpy(m_fileFS, fileFragmentShader);

	return 0;
}

void CBaseShader::LocateParams()
{
	//locate vertex attribs
	m_positionAttribute = glGetAttribLocation(m_program, "a_posL");
	m_uvAttribute = glGetAttribLocation(m_program, "a_uv");
}

CBaseShader::~CBaseShader()
{
	glDeleteProgram(m_program);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
}