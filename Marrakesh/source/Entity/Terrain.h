#pragma once
#include "Mesh.h"
#include "../../Util/include/Defines.h"


class Terrain : public Mesh
{
public:
	Terrain();
	~Terrain();

	int Load(const char * filePath) override;
	//void Draw() override;
	//void BindBuffers() override;

private:

	int m_numVertsPerRow;
	int m_numVertsPerCol;

	int m_numCellsPerRow;
	int m_numCellsPerCol;

	float m_cellSpacing;
	float m_width;
	float m_depth;

	unsigned int m_numTriangles;

	PArray<float> m_pheightMap;

	void ComputeVertices();
	void ComputeIndices();
	void ComputeNormals();
};