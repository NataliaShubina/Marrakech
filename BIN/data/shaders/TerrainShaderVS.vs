attribute vec3 a_posL;
attribute vec2 a_uv;

uniform mat4 mtxMVP;
uniform float tiling;

varying vec2 v_uv;
varying float v_tiling;

void main()
{
	vec4 posL = mtxMVP * vec4(a_posL, 1.0);
	gl_Position = posL;

	v_uv = a_uv;
	v_tiling = tiling;
}