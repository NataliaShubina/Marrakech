#include "stdafx.h"
#include "CCTerrain.h"
#include "Globals.h"
#include <fstream>

CCTerrain::CCTerrain() :
	m_numVertsPerRow(0),
	m_numVertsPerCol(0),
	m_numCellsPerRow(0),
	m_numCellsPerCol(0),
	m_cellSpacing(0),
	m_width(0.0f),
	m_depth(0.0f),
	m_numTriangles(0),
	m_pheightMap(nullptr)
{

}

CCTerrain::~CCTerrain()
{
	SAFEDELARR(m_pheightMap);
}

int CCTerrain::Init(const char * filePath)
{
	std::ifstream inFileCheck(filePath, std::ios_base::binary | std::ios::ate);
	std::ifstream inFile(filePath, std::ios_base::binary);

	if (!inFile)
		return -1;

	char inBuffer[sizeof(char)];
	m_usNumOfVertices = inFileCheck.tellg() / sizeof(char);
	inFileCheck.close();

	m_pheightMap = new float[m_usNumOfVertices];

	int it = 0;
	unsigned char value;

	while (inFile.read((char*)inBuffer, sizeof(inBuffer)))
	{
		memcpy(&value, inBuffer, sizeof(char));
		m_pheightMap[it] = (float)value;
		it++;
	}

	inFile.close();

	m_numVertsPerRow = sqrt(m_usNumOfVertices);
	m_numVertsPerCol = m_numVertsPerRow;

	m_numCellsPerRow = m_numVertsPerRow - 1;
	m_numCellsPerCol = m_numVertsPerCol - 1;

	m_cellSpacing = 1.0f;

	m_width = m_numCellsPerRow * m_cellSpacing;
	m_depth = m_numCellsPerCol * m_cellSpacing;

	m_usNumOfVertices = m_numVertsPerRow * m_numVertsPerCol;
	m_numTriangles = m_numCellsPerRow * m_numCellsPerCol * 2;

	ComputeVertices();
	ComputeIndices();
	ComputeNormals();

	return 0;
}

void CCTerrain::ComputeVertices()
{

	float startX = -m_width / 2.0f;
	float startZ = -m_depth / 2.0f;

	float endX = m_width / 2.0f;
	float endZ = m_depth / 2.0f;

	float uCoordIncSize = 1.0f / (float)m_numCellsPerRow;
	float vCoordIncSize = 1.0f / (float)m_numVertsPerCol;

	m_vertices = new Vertex[m_usNumOfVertices];
	unsigned int index = 0;
	int i = 0;
	for (float z = startZ; z <= endZ; z += 1.0f)
	{
		int j = 0;
		for (float x = startX; x <= endX; x += 1.0f)
		{
			index = i * m_numVertsPerRow + j;

			m_vertices[index].pos.x = (float)x;
			m_vertices[index].pos.y = (float)m_pheightMap[index] * 0.05f;
			m_vertices[index].pos.z = (float)z;

			m_vertices[index].uv.x = (float)j * uCoordIncSize;
			m_vertices[index].uv.y = 1.0f - (float)i * vCoordIncSize;

			j++;
		}
		i++;
	}
}

void CCTerrain::ComputeIndices()
{
	m_indices = new unsigned short[m_numTriangles * 3];

	unsigned int baseIndex = 0;
	for (unsigned int i = 0; i < m_numCellsPerCol; i++)
	{
		for (unsigned int j = 0; j < m_numCellsPerRow; j++)
		{

			m_indices[baseIndex] = i * m_numVertsPerRow + j;
			m_indices[baseIndex + 1] = i * m_numVertsPerRow + j + 1;
			m_indices[baseIndex + 2] = (i + 1) * m_numVertsPerRow + j;

			m_indices[baseIndex + 3] = (i + 1) * m_numVertsPerRow + j;
			m_indices[baseIndex + 4] = i * m_numVertsPerRow + j + 1;
			m_indices[baseIndex + 5] = (i + 1) * m_numVertsPerRow + j + 1;

			baseIndex += 6;
		}
	}
}

void CCTerrain::ComputeNormals()
{
	m_usNumOfIndices = m_numTriangles * 3;

	for (unsigned int i = 0; i < m_usNumOfIndices; i += 3)
	{
		Vector3 v0 = m_vertices[m_indices[i + 0]].pos;
		Vector3 v1 = m_vertices[m_indices[i + 1]].pos;
		Vector3 v2 = m_vertices[m_indices[i + 2]].pos;

		Vector3 normal = (v1 - v0).Cross(v2 - v0);
		normal.Normalize();

		m_vertices[m_indices[i + 0]].norm = -normal;
		m_vertices[m_indices[i + 1]].norm = -normal;
		m_vertices[m_indices[i + 2]].norm = -normal;
	}
}

void CCTerrain::Draw()
{
	glDrawElements(GL_TRIANGLES, m_numTriangles * 3, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CCTerrain::BindBuffers()
{
	glGenBuffers(1, &m_vboid);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboid);
	glBufferData(GL_ARRAY_BUFFER, m_usNumOfVertices * sizeof(Vertex), m_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_iboid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numTriangles * 3 * sizeof(unsigned short), m_indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	SAFEDELARR(m_vertices);
	SAFEDELARR(m_indices);
}