precision highp float;

uniform sampler2D u_textures2d[]; 

varying vec2 v_uv;
varying float v_tiling;

void main()
{
	vec4 color = texture2D(u_textures2d[0], v_uv * v_tiling);
	gl_FragColor = vec4(color.rgb, 1.0);
}
