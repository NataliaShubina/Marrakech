#include "GridCell.h"
#include "../Marrakesh/source/Entity/Mesh.h"
#include "../Marrakesh/source/Shaders/Shader.h"
#include <stdio.h>

GridCell::GridCell() :
	m_leftTop(0.f, 0.f, 0.f),
	m_rightBottom(0.f, 0.f, 0.f),
	m_center(0.f, 0.f, 0.f),
	m_gridPosition(0.f, 0.f),
	m_width(0.f),
	m_height(0.f)
{

}

GridCell::~GridCell()
{

}

int GridCell::Init(const math::vec3& leftCorner, const math::vec2& gridPosition, float width, float height)
{

	m_gridPosition = gridPosition;
	m_width = width;
	m_height = height;

	m_leftTop.x = leftCorner.x + m_gridPosition.y * m_width;
	m_leftTop.y = leftCorner.y;
	m_leftTop.z = leftCorner.z + m_gridPosition.x * m_height;

	m_rightBottom.x = m_leftTop.x + m_width;
	m_rightBottom.y = m_leftTop.y;
	m_rightBottom.z = m_leftTop.z + m_height;

	m_center.x = m_leftTop.x + m_width / 2.f;
	m_center.y = m_leftTop.y;
	m_center.z = m_leftTop.z - m_height / 2.f;

	printf(" %f  %f  %f Top Left [%i, %i]\n", (float)(m_leftTop.x), (float)(m_leftTop.y), (float)(m_leftTop.z), (int)(m_gridPosition.x), (int)(m_gridPosition.y) );

	return 0;
}

void GridCell::SetLeftTop(const math::vec3& leftTop)
{
	m_leftTop.x = leftTop.x;
	m_leftTop.y = leftTop.y;
	m_leftTop.z = leftTop.z;

	m_rightBottom.x = m_leftTop.x + m_width;
	m_rightBottom.y = m_leftTop.y;
	m_rightBottom.z = m_leftTop.z + m_height;

	m_center.x = m_leftTop.x + m_width / 2.f;
	m_center.y = m_leftTop.y;
	m_center.z = m_leftTop.z - m_height / 2.f;
}


bool GridCell::IsPointerOnCell(const math::vec2& pointer) const
{

	if ((m_leftTop.x <= pointer.x && pointer.x <= m_rightBottom.x) &&
		(m_leftTop.y >= pointer.y && pointer.y <= m_rightBottom.y))
		return true;

	return false;
}

void GridCell::SetRightNeighbour(SharedPtr<GridCell> right)
{
	m_rigtNeighbour = right;
}

void GridCell::SetLeftNeighbour(SharedPtr<GridCell> left)
{
	m_leftNeighbour = left;
}

void GridCell::SetTopNeighbour(SharedPtr<GridCell> top)
{
	m_topNeighbour = top;
}

void GridCell::SetBottomNeighbour(SharedPtr<GridCell> bottom)
{
	m_bottomNeighbour = bottom;
}