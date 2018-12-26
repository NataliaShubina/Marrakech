precision mediump float;

uniform sampler2D u_textures2d; 
uniform float u_limit;

varying vec2 v_uv;

void main()
{
	vec3 color = texture2D(u_textures2d, v_uv).rgb;
	float brightness = 0.3 * color.r + 0.59 * color.g + 0.11 * color.b;
	float val = step(u_limit, brightness);
	gl_FragColor = vec4(color * val, 1.0);
}
