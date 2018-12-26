precision mediump float;

varying vec3 v_pos;

uniform samplerCube u_texturesCube[1];

void main()
{
	gl_FragColor = textureCube(u_texturesCube[0], v_pos);
}
