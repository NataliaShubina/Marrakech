attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec3 a_norm;

uniform mat4 u_mtxMVP;
uniform mat4 u_mtxToWorld;

varying vec3 v_posW;
varying vec3 v_normW;
varying vec3 v_binormW;
varying vec3 v_tgtW;
varying vec2 v_uv;


void main()
{
	vec4 posL = u_mtxMVP * vec4(a_posL, 1.0);
	gl_Position = posL;
	v_uv = a_uv;
	v_posW = (u_mtxToWorld * vec4(a_posL, 1.0)).xyz;
	v_normW = normalize(u_mtxToWorld * vec4(a_norm, 0.0)).xyz;
}
   