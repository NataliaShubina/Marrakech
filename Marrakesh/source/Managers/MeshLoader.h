#pragma once

#include "../../Util/include/Singleton.h"
#include "../../Util/include/Defines.h"

class Mesh;
class Terrain;

class MeshLoader : public Singleton<MeshLoader>
{
public:

	MeshLoader();
	~MeshLoader();

	int					LoadMeshes(const char * filepath);
	SharedPtr<Mesh>		GetMeshById(unsigned short id);
	SharedPtr<Terrain>  GetTerrain() const { return m_terrain; };
	int					GetMeshesNum() const { return m_uNumModel; }



private:
	unsigned int				m_uNumModel;
	PArray<SharedPtr<Mesh>>		m_models;
	SharedPtr<Terrain>			m_terrain{ nullptr };

	void Release();
};