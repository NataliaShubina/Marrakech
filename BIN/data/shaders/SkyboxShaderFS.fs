precision highp float;

uniform samplerCube u_texturesCube[];

varying vec3 v_pos;

void main()
{
	gl_FragColor = textureCube(u_texturesCube[0], v_pos);
}
