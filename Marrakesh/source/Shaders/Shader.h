#pragma once
#include "../Utilities/utilities.h"
#include "../../Util/Math.h"

class Texture;
struct Vertex;

class Shader
{
public:

	~Shader();

	int				Init(char * fileVertexShader, char * fileFragmentShader);

	const GLuint&	GetProgramHandler() const { return m_program; }

	void Use();

	void SetBool(const char * name, bool value)		const;
	void SetInt(const char * name, int value)		const;
	void SetFloat(const char * name, float value)	const;

	void SetVertexAttributes()	const;

	void SetTextures(const char * name, unsigned int size, const GLuint * value) const;

	void SetMatrix4x4F(const char * name, const math::Matrix& value) const;
	void Set3VectorF(const char * name, const math::vec3& value)	 const;

	void BindBuffers(GLuint vbo, GLuint ibo);

protected:

	GLuint m_program;
	GLuint m_vertexShader; 
	GLuint m_fragmentShader;
};