#pragma once
#include "../../Util/Math.h"

struct Vertex
{
	math::vec3 position{ 0.0f, 0.0f, 0.0f };
	math::vec3 normals{ 0.0f, 0.0f, 0.0f };
	math::vec2 uv{ 0.0f, 0.0f };

	Vertex(){}
	Vertex(math::vec3, math::vec3, math::vec2);
};
