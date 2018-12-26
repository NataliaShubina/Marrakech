#include "Vertex.h"

Vertex::Vertex(math::vec3 _pos, math::vec3 _norm, math::vec2 _uv)
{
	position = _pos;
	normals = _norm;
	uv = _uv;
}