#pragma once
#include "Vertex.h"
#include "../Utilities/utilities.h"

class CModel
{
public:

	CModel();
	virtual ~CModel();

	virtual int Init(const char * filePath);
	virtual const GLuint GetVertBufferId() const { return m_vboid; }
	virtual const GLuint GetIndexBufferId() const { return m_iboid; }
	virtual void BindBuffers();
	virtual void Draw();

protected:

	GLuint m_vboid;
	GLuint m_iboid;

	unsigned int m_usNumOfIndices;
	unsigned int m_usNumOfVertices;

	Vertex * m_vertices;
	unsigned short * m_indices;
};