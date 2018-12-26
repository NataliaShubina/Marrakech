precision mediump float;

varying vec2 v_uv;
uniform sampler2D u_textures2d[2]; 

void main()
{
	vec4 color = texture2D(u_textures2d[0], v_uv);
	vec4 blur = texture2D(u_textures2d[1], v_uv);
	gl_FragColor = color + 1.2 * blur;
}