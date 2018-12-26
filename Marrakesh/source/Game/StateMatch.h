#pragma once
#include "State.h"
#include "../Marrakesh/Util/include/Defines.h"

class Scene;
class Widget;


class StateMatch : public State
{
public:
	StateMatch();
	virtual ~StateMatch();

	virtual int  Init() override;
	virtual void SetupGui() override;
	virtual void Render() override;
	virtual void OnKeyPressed() override;
	virtual void OnMouseBtn(char btn, bool pressed, const math::vec3& position) override;
	virtual void OnKeyReleased() override;

	SharedPtr<Scene> GetScene() const { return m_scene; }

protected:
	virtual void RenderGui() override;

private:

	SharedPtr<Scene>	m_scene;
};