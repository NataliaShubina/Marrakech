precision highp float;

uniform sampler2D u_textures2d[]; 

varying vec2 v_uv;

void main()
{
	gl_FragColor = texture2D(u_textures2d[0], v_uv);
}
