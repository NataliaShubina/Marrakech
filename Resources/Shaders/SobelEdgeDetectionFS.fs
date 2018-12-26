precision mediump float;

varying vec2 v_uv;

uniform sampler2D u_textures2d; 
uniform float u_height;
uniform float u_width;

void main()
{
	vec4 n[9];

	n[0] = texture2D(u_textures2d, v_uv + vec2(  -u_width, -u_height));
	n[1] = texture2D(u_textures2d, v_uv + vec2(		  0.0, -u_height));
	n[2] = texture2D(u_textures2d, v_uv + vec2(   u_width, -u_height));
	n[3] = texture2D(u_textures2d, v_uv + vec2(  -u_width,  0.0));
	n[4] = texture2D(u_textures2d, v_uv);
	n[5] = texture2D(u_textures2d, v_uv + vec2(	  u_width, 0.0));
	n[6] = texture2D(u_textures2d, v_uv + vec2(  -u_width, u_height));
	n[7] = texture2D(u_textures2d, v_uv + vec2(       0.0, u_height));
	n[8] = texture2D(u_textures2d, v_uv + vec2(   u_width, u_height));

	vec4 sobelEdgeU = n[2] + (2.0 * n[5]) + n[8] - (n[0] + (2.0 * n[3]) + n[6]);
  	vec4 sobelEdgeV = n[0] + (2.0 * n[1]) + n[2] - (n[6] + (2.0 * n[7]) + n[8]);
	vec4 sobel = sqrt((sobelEdgeU * sobelEdgeU) + (sobelEdgeV * sobelEdgeV));

	gl_FragColor = vec4(vec3(0.3 * sobel.r + 0.59 * sobel.g + 0.11 * sobel.b), 1.0 );
}