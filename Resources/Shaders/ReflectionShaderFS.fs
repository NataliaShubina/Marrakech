precision mediump float;

uniform vec3 u_camPosition;
uniform samplerCube u_texturesCube[];

varying vec3 v_posW;
varying vec3 v_normW;


void main()
{
	vec3 eyeDir = u_camPosition - v_posW;
	vec3 reflectDir = reflect(normalize(-eyeDir), normalize(v_normW));  
	gl_FragColor = textureCube(u_texturesCube[0], reflectDir);
}
