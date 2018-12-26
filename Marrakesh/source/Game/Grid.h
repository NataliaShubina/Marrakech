#pragma once
#include "../Marrakesh/Util/include/Defines.h"
#include "../Marrakesh/Util/Math.h"

class GridCell;
class Scene;

class Grid
{
public:
	Grid();
	~Grid();

	int Init(SharedPtr<Scene> scene);
	void Render();

	const PArray<SharedPtr<GridCell>>	GetGrid() const { return m_grid; }
	const SharedPtr<GridCell>			GetCellByPosition(const math::vec2& coord) const { return m_grid[coord.x + coord.y * GRID_SIZE]; }
	SharedPtr<GridCell>					GetCellByPointerCoord(const math::vec2& coord) const;

	void	ConvertToWolrd();

private:

	SharedPtr<Scene>			m_scene;
	PArray<SharedPtr<GridCell>> m_grid;

	math::Matrix				m_localToWorld;
};