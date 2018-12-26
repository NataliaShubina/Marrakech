#include "Grid.h"
#include "GridCell.h"
#include "../Marrakesh//source/Entity/Mesh.h"
#include "../Marrakesh/source/Managers/MeshLoader.h"
#include "Scene.h"
#include "Object.h"

Grid::Grid()
{
	m_grid.reserve(GRID_SIZE * GRID_SIZE);
}

Grid::~Grid()
{

}

SharedPtr<GridCell> Grid::GetCellByPointerCoord(const math::vec2& coord) const
{
	for (int i = 0; i < m_grid.size(); i++)
	{
		if (m_grid[i]->IsPointerOnCell(coord))
			return m_grid[i];
	}
	return nullptr;
}

void Grid::ConvertToWolrd()
{
	for (int i = 0; i < m_grid.size(); i++)
	{
		math::vec4 position = math::vec4(m_grid[i]->GetLeftTop(), 1.0f) * m_localToWorld;
		m_grid[i]->SetLeftTop(math::vec3(position.x, position.y, position.z));
	}
}


int Grid::Init(SharedPtr<Scene> scene)
{
	m_scene = scene;
	auto& deck = m_scene->GetObj(1);
	m_localToWorld = deck->GetWorldMatrix();
	SharedPtr<Mesh> mesh = deck->GetModel();
	auto vertices = mesh->GetVertexArray();

	math::vec3 startPosition(0.f, 0.f, 0.f);
	Vertex topLeft;
	math::vec3 position;

	float highest = 0.f;

	for (int i = 0; i < vertices.size(); i++)
	{
		if (highest < vertices[i].position.y)
			highest = vertices[i].position.y;
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		position = vertices[i].position;

		if (position.y == position.y &&
			(position.x < topLeft.position.x || position.y < topLeft.position.y))
			topLeft = vertices[i];
	}

	math::vec2 gridPosition(0.f, 0.f);

	auto worldPosition = math::vec4(topLeft.position.x, topLeft.position.y, topLeft.position.z, 1.0) * deck->GetWorldMatrix();
	topLeft.position = math::vec3(worldPosition.x, worldPosition.y, worldPosition.z);

	float cellWidth = (fabsf(topLeft.position.x) * 2) / (float)GRID_SIZE;
	float cellHeight = (fabsf(topLeft.position.z) * 2) / (float)GRID_SIZE;

	for (int i = 0; i < GRID_SIZE; i++)
	{
		gridPosition.x = i;

		for (int j = 0; j < GRID_SIZE; j++)
		{
			gridPosition.y = j;

			SharedPtr<GridCell> cell = std::make_shared <GridCell> ();
			cell->Init(topLeft.position, gridPosition, cellWidth, cellHeight);
			m_grid.push_back(cell);
		}
	}

	//fill right neighbours
	int index = 0;

	for (int j = 0; j < GRID_SIZE; j++)
	{
		for (int i = 0; i < GRID_SIZE - 1; i++)
		{
			index = i + j * GRID_SIZE;

			m_grid[index]->SetRightNeighbour(m_grid[index + 1]);
		}
	}

	//fill left neighbours
	index = 0;

	for (int j = 0; j < GRID_SIZE; j++)
	{
		for (int i = 1; i < GRID_SIZE; i++)
		{
			index = i + j * GRID_SIZE;

			m_grid[index]->SetLeftNeighbour(m_grid[index - 1]);
		}
	}

	//fill bottom neighbours
	index = 0;

	for (int j = 0; j < GRID_SIZE; j++)
	{
		for (int i = 0; i < GRID_SIZE - 1; i++)
		{
			index = i * GRID_SIZE  + j;

			m_grid[index]->SetBottomNeighbour(m_grid[index + GRID_SIZE]);
		}
	}

	//fill top neighbours
	index = 0;

	for (int j = 0; j < GRID_SIZE; j++)
	{
		for (int i = 1; i < GRID_SIZE; i++)
		{
			index = i * GRID_SIZE + j;

			m_grid[index]->SetTopNeighbour(m_grid[index - GRID_SIZE]);
		}
	}

	m_grid[0]->SetLeftNeighbour(m_grid[0]);
	m_grid[0]->SetTopNeighbour(m_grid[0]);

	m_grid[1]->SetTopNeighbour(m_grid[2]);
	m_grid[2]->SetTopNeighbour(m_grid[1]);

	m_grid[3]->SetTopNeighbour(m_grid[4]);
	m_grid[4]->SetTopNeighbour(m_grid[3]);

	m_grid[5]->SetTopNeighbour(m_grid[6]);
	m_grid[6]->SetTopNeighbour(m_grid[5]);
	m_grid[6]->SetRightNeighbour(m_grid[13]);

	m_grid[7]->SetLeftNeighbour(m_grid[14]);
	m_grid[13]->SetRightNeighbour(m_grid[6]);

	m_grid[14]->SetLeftNeighbour(m_grid[7]);
	m_grid[20]->SetRightNeighbour(m_grid[27]);

	m_grid[21]->SetLeftNeighbour(m_grid[28]);
	m_grid[27]->SetRightNeighbour(m_grid[20]);

	m_grid[28]->SetLeftNeighbour(m_grid[21]);
	m_grid[34]->SetRightNeighbour(m_grid[41]);

	m_grid[35]->SetLeftNeighbour(m_grid[42]);
	m_grid[41]->SetRightNeighbour(m_grid[34]);

	m_grid[42]->SetLeftNeighbour(m_grid[35]);
	m_grid[42]->SetBottomNeighbour(m_grid[43]);
	m_grid[43]->SetBottomNeighbour(m_grid[42]);

	m_grid[44]->SetBottomNeighbour(m_grid[45]);
	m_grid[45]->SetBottomNeighbour(m_grid[44]);

	m_grid[46]->SetBottomNeighbour(m_grid[47]);
	m_grid[47]->SetBottomNeighbour(m_grid[46]);

	m_grid[48]->SetRightNeighbour(m_grid[48]);
	m_grid[48]->SetBottomNeighbour(m_grid[48]);

	return 0;
}