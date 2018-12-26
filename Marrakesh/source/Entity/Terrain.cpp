#include "Terrain.h"
#include "../../Util/include/TGA.h"
#include "../Utilities/utilities.h"
#include <fstream>

Terrain::Terrain() :
	m_numVertsPerRow(0),
	m_numVertsPerCol(0),
	m_numCellsPerRow(0),
	m_numCellsPerCol(0),
	m_cellSpacing(0),
	m_width(0.0f),
	m_depth(0.0f),
	m_numTriangles(0)
{
	m_pheightMap.resize(0);
}

Terrain::~Terrain()
{
	m_pheightMap.resize(0);
}

int Terrain::Load(const char * filePath)
{
	int width, height, bpp;
	char * bufferTGA = LoadTGA(filePath, &width, &height, &bpp);

	m_uNumVertices = width * height;
	unsigned int filesize = width * height *bpp / 8;

	unsigned char valueR;
	unsigned char valueG;
	unsigned char valueB;

	for (auto i = 0; i < filesize; i += 4)
	{
		memcpy(&valueB, &bufferTGA[i], sizeof(char));
		memcpy(&valueG, &bufferTGA[i+1], sizeof(char));
		memcpy(&valueR, &bufferTGA[i+2], sizeof(char));

		m_pheightMap.push_back((((float)valueB + (float)valueG + (float)valueR)/3.f));
	}
	m_numVertsPerRow = sqrt(m_uNumVertices);
	m_numVertsPerCol = m_numVertsPerRow;

	m_numCellsPerRow = m_numVertsPerRow - 1;
	m_numCellsPerCol = m_numVertsPerCol - 1;

	m_cellSpacing = 1.0f;

	m_width = m_numCellsPerRow * m_cellSpacing;
	m_depth = m_numCellsPerCol * m_cellSpacing;

	m_uNumVertices = m_numVertsPerRow * m_numVertsPerCol;
	m_numTriangles = m_numCellsPerRow * m_numCellsPerCol * 2;

	ComputeVertices();
	ComputeIndices();
	ComputeNormals();

	return 0;
}

void Terrain::ComputeVertices()
{

	float startX = -m_width / 2.0f;
	float startZ = -m_depth / 2.0f;

	float endX = m_width / 2.0f;
	float endZ = m_depth / 2.0f;

	float uCoordIncSize = 1.0f / (float)m_numCellsPerRow;
	float vCoordIncSize = 1.0f / (float)m_numVertsPerCol;

	m_vertices.resize(m_uNumVertices);
	unsigned int index = 0;
	int i = 0;
	for (float z = startZ; z <= endZ; z += 1.0f)
	{
		int j = 0;
		for (float x = startX; x <= endX; x += 1.0f)
		{
			index = i * m_numVertsPerRow + j;

			m_vertices[index].position.x = (float)x;
			m_vertices[index].position.y = (float)m_pheightMap[index] * 0.05f;
			m_vertices[index].position.z = (float)z;

			m_vertices[index].uv.x = (float)j * uCoordIncSize;
			m_vertices[index].uv.y = 1.0f - (float)i * vCoordIncSize;

			j++;
		}
		i++;
	}
}

void Terrain::ComputeIndices()
{

	m_indices.resize(m_numTriangles * 3);

	unsigned int baseIndex = 0;
	for (auto i = 0; i < m_numCellsPerCol; i++)
	{
		for (auto j = 0; j < m_numCellsPerRow; j++)
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

void Terrain::ComputeNormals()
{
	m_uNumIndices = m_numTriangles * 3;

	for (unsigned int i = 0; i < m_uNumIndices; i += 3)
	{
		math::vec3 v0 = m_vertices[m_indices[i + 0]].position;
		math::vec3 v1 = m_vertices[m_indices[i + 1]].position;
		math::vec3 v2 = m_vertices[m_indices[i + 2]].position;

		math::vec3 normal = (v1 - v0).Cross(v2 - v0);
		normal.Normalize();

		m_vertices[m_indices[i + 0]].normals = -normal;
		m_vertices[m_indices[i + 1]].normals = -normal;
		m_vertices[m_indices[i + 2]].normals = -normal;
	}
}

//void Terrain::Draw()
//{
//	glDrawElements(GL_TRIANGLES, m_uNumIndices, GL_UNSIGNED_SHORT, 0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//}
//
//void Terrain::BindBuffers()
//{
//	glGenBuffers(1, &m_vbo);
//	glGenBuffers(1, &m_ibo);
//
//	Vertex * vertices = new Vertex[m_uNumVertices];
//	vertices = m_vertices.data();
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_uNumVertices, vertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	unsigned short * indices = new unsigned short[m_numTriangles * 3];
//	indices = m_indices.data();
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_numTriangles * 3, indices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	
//	m_vertices.resize(0);
//	m_indices.resize(0);
//}