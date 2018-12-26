#pragma once

#include "Vertex.h"
#include "../../Util/include/Defines.h"

typedef unsigned int GLuint;

class Mesh
{
public:
	Mesh();
	~Mesh();

	virtual int		Load(const char * path);
	const GLuint	GetVerttexBuffer() const { return m_vbo; }
	const GLuint	GetIndexBuffer()	const { return m_ibo; }

	void SetVertexArray(const PArray<Vertex>& vertices);
	void SetIndexArray(const PArray<unsigned short>& indices);

	const PArray<Vertex>& GetVertexArray() const { return m_vertices; }

	virtual void BindBuffers();
	virtual void Draw();

protected:

	GLuint m_vbo;
	GLuint m_ibo;
	GLuint m_vao;

	PArray<Vertex>			m_vertices;
	PArray<unsigned short>	m_indices;

	unsigned int m_uNumIndices;
	unsigned int m_uNumVertices;
};