attribute vec3 a_posL;
attribute vec3 a_norm;
attribute vec2 a_uv;

uniform float a_tFactor;

varying float v_tFactor;

uniform mat4 u_mtxMVP;
uniform mat4 u_mtxToWorld;

varying vec3 v_normW;
varying vec3 v_posW;
varying vec2 v_uv;

void main()
{
	vec4 posL = u_mtxMVP * vec4(a_posL, 1.0);
	gl_Position = posL;

	v_posW = (u_mtxToWorld * vec4(a_posL, 1.0)).xyz;
	v_normW = normalize(u_mtxToWorld * vec4(a_norm, 0.0)).xyz;
	v_uv = a_uv;
	v_tFactor = a_tFactor;
}
   