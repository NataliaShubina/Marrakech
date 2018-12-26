#pragma once
#include "CModel.h"

class CCTerrain : public CModel
{
public:
	CCTerrain();
	~CCTerrain();
	
	int Init(const char * filePath);
	void Draw();
	void BindBuffers();

private:

	int m_numVertsPerRow;
	int m_numVertsPerCol;

	int m_numCellsPerRow;
	int m_numCellsPerCol;

	float m_cellSpacing;
	float m_width;
	float m_depth;

	unsigned int m_numVertices;
	unsigned int m_numTriangles;

	float * m_pheightMap;

	void ComputeVertices();
	void ComputeIndices();
	void ComputeNormals();
};