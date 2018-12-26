precision mediump float;

varying vec2 v_uv;

uniform sampler2D u_textures2d[]; //dispmap

uniform float u_Time;
uniform float u_dMax;

void main()
{
	vec2 disp = texture2D(u_textures2d[0], vec2(v_uv.x, v_uv.y + u_Time)).rg;
	vec2 offset = (2.0 * disp - 1.0) * u_dMax;
	
	vec2 new_uv = v_uv + offset;

	vec4 fire_color = texture2D (u_textures2d[1], new_uv);

	vec4 AlphaValue = texture2D(u_textures2d[2], v_uv);

	fire_color = fire_color * (1.0, 1.0, 1.0, AlphaValue.r);
	
	if (fire_color.a < 0.1)
		discard;

	gl_FragColor = fire_color;

}
