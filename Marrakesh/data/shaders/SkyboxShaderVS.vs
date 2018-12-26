attribute vec3 a_posL;

uniform mat4 mtxMVP;

varying vec3 v_pos;

void main()
{
	vec4 posL = mtxMVP * vec4(a_posL, 1.0);
	gl_Position = posL;
	v_pos = a_posL;
}
