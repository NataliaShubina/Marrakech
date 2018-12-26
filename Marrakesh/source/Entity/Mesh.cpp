#include "Mesh.h"
#include "../Utilities/utilities.h"

Mesh::Mesh() :
	m_vbo(0),
	m_ibo(0), 
	m_vao(0), 
	m_uNumIndices(0),
	m_uNumVertices(0)
{
	m_vertices.resize(0);
	m_indices.resize(0);
}

Mesh::~Mesh()
{
	m_vertices.resize(0);
	m_indices.resize(0);

	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}


bool IsNear(float v1, float v2)
{
	return (fabs(v1 - v2) < 0.01f);
}
//
//bool IsEqual(const Vertex& v1, const Vertex& v2)
//{
//
//	if (IsNear(v1.position.x, v2.position.x) &&
//		IsNear(v1.position.y, v2.position.y) &&
//		IsNear(v1.position.z, v2.position.z) &&
//		
//		IsNear(v1.uv.x, v2.uv.x) &&
//		IsNear(v1.uv.y, v2.uv.y) &&
//
//		IsNear(v1.normals.x, v2.normals.x) &&
//		IsNear(v1.normals.y, v2.normals.y) &&
//		IsNear(v1.normals.z, v2.normals.z)
//		)
//	{
//		return true;
//	}
//
//	return false;
//}


bool IsEqual (Vertex v1, Vertex v2)
{

	if (IsNear(v1.position.x, v2.position.x) &&
		IsNear(v1.position.y, v2.position.y) &&
		IsNear(v1.position.z, v2.position.z) &&
		IsNear(v1.uv.x, v2.uv.x) &&
		IsNear(v1.uv.y, v2.uv.y) &&
		IsNear(v1.normals.x, v2.normals.x) &&
		IsNear(v1.normals.y, v2.normals.y) &&
		IsNear(v1.normals.z, v2.normals.z)
		)
	{
		return  true;
	}

	return false;
}

int GetSimilarVertexIndex(const Vertex& vertex, PArray<Vertex>& vertices)
{
	for (auto i = 0; i < vertices.size(); i++)
	{
		if (IsEqual(vertex, vertices[i]))
		{
			return i;
		}
		else
		{
			continue;
		}
	}
	vertices.push_back(vertex);
	return (vertices.size() - 1);\
}

int Mesh::Load(const char * path)
{
	PArray<math::vec3> tmpPos;
	PArray<math::vec2> tmpUV;
	PArray<math::vec3> tmpN;
	PArray<Vertex> vertexFaces;

	FILE * pFile;
	pFile = fopen(path, "rb");
	
	PASSERT(pFile != NULL, "Cannot open mesh file!");
	if (pFile == NULL)
		return -1;

	unsigned short vIndex[4], uvIndex[4], normIndex[4];

	while (true)
	{
		char lineHeader[128];
		int res = fscanf(pFile, "%s", lineHeader);
		if (res == EOF)
			break;

		Vertex vertex;

		if (strcmp(lineHeader, "v") == 0)
		{
			math::vec3 pos;
			fscanf(pFile, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
			tmpPos.push_back(pos);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			math::vec2 uv;
			fscanf(pFile, "%f %f\n", &uv.x, &uv.y);
			tmpUV.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			math::vec3 norm;
			fscanf(pFile, "%f %f %f\n", &norm.x, &norm.y, &norm.z);
			tmpN.push_back(norm);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			int matches = fscanf(pFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vIndex[0], &uvIndex[0], &normIndex[0], &vIndex[1], &uvIndex[1], &normIndex[1], &vIndex[2], &uvIndex[2], &normIndex[2]);
			
			PASSERT(matches == 9, "Matches != 9!");

			if (matches != 9)
			{
				return -2;
			}

			Vertex vertices[3];

			//set positions
			vertices[0].position.x = tmpPos[vIndex[0] - 1].x;
			vertices[0].position.y = tmpPos[vIndex[0] - 1].y;
			vertices[0].position.z = tmpPos[vIndex[0] - 1].z;

			vertices[1].position.x = tmpPos[vIndex[1] - 1].x;
			vertices[1].position.y = tmpPos[vIndex[1] - 1].y;
			vertices[1].position.z = tmpPos[vIndex[1] - 1].z;

			vertices[2].position.x = tmpPos[vIndex[2] - 1].x;
			vertices[2].position.y = tmpPos[vIndex[2] - 1].y;
			vertices[2].position.z = tmpPos[vIndex[2] - 1].z;

			// set uv coords
			vertices[0].uv.x = tmpUV[uvIndex[0]-1].x;
			vertices[0].uv.y = tmpUV[uvIndex[0]-1].y;

			vertices[1].uv.x = tmpUV[uvIndex[1]-1].x;
			vertices[1].uv.y = tmpUV[uvIndex[1]-1].y;

			vertices[2].uv.x = tmpUV[uvIndex[2]-1].x;
			vertices[2].uv.y = tmpUV[uvIndex[2]-1].y;

			// link vertices and uv coords
			vertices[0].normals.x = tmpN[normIndex[0]-1].x;
			vertices[0].normals.y = tmpN[normIndex[0]-1].y;
			vertices[0].normals.z = tmpN[normIndex[0]-1].z;

			vertices[1].normals.x = tmpN[normIndex[1]-1].x;
			vertices[1].normals.y = tmpN[normIndex[1]-1].y;
			vertices[1].normals.z = tmpN[normIndex[1]-1].z;

			vertices[2].normals.x = tmpN[normIndex[2]-1].x;
			vertices[2].normals.y = tmpN[normIndex[2]-1].y;
			vertices[2].normals.z = tmpN[normIndex[2]-1].z;

			vertexFaces.push_back(vertices[0]);
			vertexFaces.push_back(vertices[1]);
			vertexFaces.push_back(vertices[2]);
		}
	}

	// getting unique vertices and creating index array

	m_vertices.push_back(vertexFaces[0]);
	m_indices.push_back(0);
	int index = 0;
	for (auto i = 1; i < vertexFaces.size(); i++)
	{
		m_indices.push_back(GetSimilarVertexIndex(vertexFaces[i], m_vertices));
	}

	m_uNumIndices = m_indices.size();
	m_uNumVertices = m_vertices.size();

	return 0;
}

void Mesh::SetVertexArray(const PArray<Vertex>& vertices)
{
	m_vertices = vertices;
	m_uNumVertices = m_vertices.size();
}
void Mesh::SetIndexArray(const PArray<unsigned short>& indices)
{
	m_indices = indices;
	m_uNumIndices = m_indices.size();
}

void Mesh::BindBuffers()
{

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_uNumVertices, &m_vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_uNumIndices, &m_indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::Draw()
{
	glDrawElements(GL_TRIANGLES, m_uNumIndices, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}