precision mediump float;

varying float v_tFactor;

uniform sampler2D u_textures2d[]; 

uniform vec3 u_camPosition;
uniform float u_fogStart;
uniform float u_fogRange;
uniform vec3 u_fogColor;

uniform vec3 u_ambColor;
uniform float u_ambWeight;

uniform vec3 u_lightColor[];
uniform vec3 u_lightPositions[];

varying vec2 v_uv;
varying vec3 v_normW;
varying vec3 v_posW;


void main()
{
	vec4 t1 = texture2D(u_textures2d[1], v_uv * v_tFactor);
	vec4 t2 = texture2D(u_textures2d[2], v_uv * v_tFactor);
	vec4 t3 = texture2D(u_textures2d[3], v_uv * v_tFactor);
	vec4 map = texture2D(u_textures2d[0], v_uv);
	vec4 terrainColor = (map.r * t2 + map.g * t1 + map.b * t3) / (map.r + map.g + map.b);

	vec3 nnorW = normalize(v_normW);
	vec3 DiffuseComponent = max(dot(nnorW, -u_lightPositions[0]), 0.0) * u_lightColor[0];
	vec4 resultColor =  vec4((mix(u_ambColor, DiffuseComponent, u_ambWeight) * terrainColor.xyz).xyz, terrainColor.w);


	float distanceFromCameraToFrag = distance(vec4(u_camPosition, 1.0), vec4(v_posW, 1.0));
	float factor = clamp((distanceFromCameraToFrag - u_fogStart)/u_fogRange, 0.0, 1.0);
	
	gl_FragColor = mix(resultColor, vec4 (u_fogColor, 1.0), factor);
}
