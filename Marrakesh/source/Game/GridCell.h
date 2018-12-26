#pragma once
#include "../Marrakesh/Util/include/Defines.h"
#include "../Marrakesh/Util/Math.h"

class Shader;
class Mesh;

class GridCell
{
public:

	GridCell();
	~GridCell();

	int Init(const math::vec3& physPostition, const math::vec2& gridPosition, float width, float height);

	bool IsPointerOnCell(const math::vec2& pointer) const;

	math::vec2 GetGridPosition() const { return m_gridPosition; }
	math::vec3 GetCenter() const { return m_center; }
	math::vec3 GetLeftTop() const { return m_leftTop; }

	void SetLeftTop(const math::vec3& leftTop);

	void SetRightNeighbour(SharedPtr<GridCell> right);
	void SetLeftNeighbour(SharedPtr<GridCell> left);
	void SetTopNeighbour(SharedPtr<GridCell> top);
	void SetBottomNeighbour(SharedPtr<GridCell> bottom);

protected:
	void GenerateMesh();

private:

	math::vec3	m_leftTop;
	math::vec3	m_rightBottom;

	math::vec3	m_center;

	math::vec2	m_gridPosition;

	float		m_width;
	float		m_height;

	SharedPtr<Mesh> m_mesh;
	SharedPtr<Shader> m_shader;

	SharedPtr<GridCell> m_leftNeighbour;
	SharedPtr<GridCell> m_rigtNeighbour;
	SharedPtr<GridCell> m_topNeighbour;
	SharedPtr<GridCell> m_bottomNeighbour;
};