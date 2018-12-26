attribute vec3 a_posL;
attribute vec3 a_color;
//attribute vec2 a_uv;
//varying vec2 v_uv;
varying vec3 v_color;
uniform mat4 u_mtxM;
uniform mat4 u_mtxV;
uniform mat4 u_mtxP;

void main()
{
vec4 posL = u_mtxP*u_mtxV* u_mtxM* vec4(a_posL, 1.0);
gl_Position = posL;
v_color = a_color;
//v_uv = a_uv;
}
   