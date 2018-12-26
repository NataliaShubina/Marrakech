#include "StateMatch.h"
#include "Scene.h"
#include "Grid.h"
#include "GridCell.h"

StateMatch::StateMatch()
{
	m_scene = std::make_shared<Scene>();
}
StateMatch::~StateMatch()
{

}

void StateMatch::SetupGui()
{

}

void StateMatch::Render()
{
	m_scene->Draw();
}

int StateMatch::Init()
{
	m_scene->Load(SCENE_PATH);

	return 0;
}

void StateMatch::RenderGui()
{

}

void StateMatch::OnKeyPressed()
{

}

void StateMatch::OnKeyReleased()
{

}

void StateMatch::OnMouseBtn(char btn, bool pressed, const math::vec3& position)
{
	switch (btn)
	{
	case LBUTTON:
	{
//		m_scene->GetGrid()->ConvertToWolrd();
		auto cell = m_scene->GetGrid()->GetCellByPointerCoord(math::vec2(position.x, position.z));		
		if (cell)
			printf("Top left (%f, %f, %f) \n Cursor position (%f, %f) \n Cell [%u][%u]\n  ",
			(float)(cell->GetLeftTop().x), (float)(cell->GetLeftTop().y), (float)(cell->GetLeftTop().z),
				(float)(position.x), (float)(position.z),
				(int)(cell->GetGridPosition().x), (int)(cell->GetGridPosition().y)
			);
	}
	break;

	default:
		break;
	}
}