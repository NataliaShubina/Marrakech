precision mediump float;

varying vec2 v_uv;

uniform sampler2D u_textures2d; 

void main()
{
	vec4 color = texture2D(u_textures2d, v_uv);
	gl_FragColor = vec4(vec3(0.3 * color.r + 0.59 * color.g + 0.11 * color.b), color.a);
}
