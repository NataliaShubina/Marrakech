precision mediump float;

varying vec2 v_uv;

uniform sampler2D u_textures2d;

void main()
{
	gl_FragColor = texture2D(u_textures2d, v_uv);
}