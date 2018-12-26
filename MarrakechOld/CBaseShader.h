#pragma once
#include "../Utilities/utilities.h"

class CBaseShader
{
public:

	virtual int Init(char * fileVertexShader, char * fileFragmentShader);

	virtual void LocateParams();

	const GLuint& GetProgramHandler() const { return m_program; }
	virtual ~CBaseShader();

protected:
	GLuint m_program, m_vertexShader, m_fragmentShader;
	char m_fileVS[260];
	char m_fileFS[260];

	//vertex attributes
	GLint m_positionAttribute;
	GLint m_uvAttribute;
};