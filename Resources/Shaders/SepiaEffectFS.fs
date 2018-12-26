precision mediump float;

varying vec2 v_uv;

uniform sampler2D u_textures2d; 

void main()
{
	vec4 color = texture2D(u_textures2d, v_uv);
	gl_FragColor = vec4(vec3(dot(color.rgb, vec3(0.393, 0.769, 0.189)), 
							dot(color.rgb, vec3(0.349, 0.686, 0.168)), 
							dot(color.rgb, vec3(0.272, 0.534, 0.131))), color.a);
}
