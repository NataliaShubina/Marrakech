#pragma once

#include "../../Util/include/Defines.h"

class Terrain;
class Object;
class Camera;
class Light;
class Fog;
class Grid;

class Scene
{
public:
	Scene();
	~Scene();

	int			Load(const char * filename);
	void		Draw();
	void		Update(float deltaTime);

	SharedPtr<Camera>	GetCamera() const { return m_camera; }
	SharedPtr<Grid>		GetGrid() const { return m_grid; }
	SharedPtr<Object>	GetObj(unsigned short id) const { return m_objects[id]; }

private:
	unsigned int m_uNumObjects;
	unsigned int m_uNumLights;

	PArray<SharedPtr<Object>>		m_objects;
	SharedPtr<Camera>				m_camera;
	SharedPtr<Grid>					m_grid;
};