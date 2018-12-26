#include "stdafx.h"
#include "CModel.h"
#include "CCamera.h"
#include "Globals.h"

CModel::CModel() :
	m_vboid(0),
	m_iboid(0),
	m_usNumOfVertices(0),
	m_usNumOfIndices(0),
	m_vertices(nullptr),
	m_indices(nullptr)
{

}

CModel::~CModel()
{
	SAFEDELARR(m_vertices);
	SAFEDELARR(m_indices);
}

int CModel::Init(const char * filePath)
{
	FILE * pFile;
	pFile = fopen(filePath, "rb");
	if (pFile == NULL)
	{
		printf("Can't readt the file!\n");
		return -1;
	}

	m_usNumOfVertices = 0;
	fscanf_s(pFile, "%*s %d", &m_usNumOfVertices);

	m_vertices = new Vertex[m_usNumOfVertices];

	for (size_t i = 0; i < m_usNumOfVertices; i++)
	{
		fscanf_s(pFile, " %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &m_vertices[i].pos.x, &m_vertices[i].pos.y, &m_vertices[i].pos.z,
			&m_vertices[i].norm.x, &m_vertices[i].norm.y, &m_vertices[i].norm.z,
			&m_vertices[i].binorm.x, &m_vertices[i].binorm.y, &m_vertices[i].binorm.z,
			&m_vertices[i].tgt.x, &m_vertices[i].tgt.y, &m_vertices[i].tgt.z,
			&m_vertices[i].uv.x, &m_vertices[i].uv.y);
	}

	m_usNumOfIndices = 0;

	fscanf_s(pFile, "%*s %d", &m_usNumOfIndices);

	m_indices = new unsigned short[m_usNumOfIndices +1];
	for (size_t i = 0; i < m_usNumOfIndices; i += 3)
	{
		fscanf_s(pFile, " %*d. %i, %i, %i", &m_indices[i], &m_indices[i + 1], &m_indices[i + 2]);
	}
	return 0;
}

void CModel::Draw()
{
	glDrawElements(GL_TRIANGLES, m_usNumOfIndices, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CModel::BindBuffers()
{
	glGenBuffers(1, &m_vboid);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_usNumOfVertices, m_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_iboid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_usNumOfIndices * sizeof(unsigned short), m_indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	SAFEDELARR(m_vertices);
	SAFEDELARR(m_indices);
}