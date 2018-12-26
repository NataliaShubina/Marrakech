precision mediump float;

uniform sampler2D u_textures2d[];

uniform vec3 u_lightColor[3];
uniform vec3 u_lightPositions[3];

uniform vec3 u_camPosition;
uniform float u_fogStart;
uniform float u_fogRange;
uniform vec3 u_fogColor;

uniform vec3 u_ambColor;
uniform float u_ambWeight;
uniform float u_specularPower;
uniform int u_mapExists;

varying vec2 v_uv;
varying vec3 v_normW;
varying vec3 v_posW;

void main()
{
	vec3 DiffuseComponent;
	vec3 SpecularComponent;
	vec3 normalW = normalize(v_normW);
	

	//specular light
	for(int i=0; i<3; i++)
	{
		vec3 lightDirection = normalize(v_posW - u_lightPositions[i]);
		//diffuse light
		DiffuseComponent += max(dot(normalW, -lightDirection), 0.0) * u_lightColor[i];

		vec3 reflectVector = normalize(reflect(lightDirection, normalW));
		vec3 toEye = normalize(u_camPosition - v_posW);
		//specular light
		SpecularComponent += pow(max(dot(reflectVector, toEye),0.0), u_specularPower) * u_lightColor[i];
	}

	vec4 color = texture2D(u_textures2d[0], v_uv);
	vec4 resultColor =  vec4((mix(u_ambColor, DiffuseComponent, u_ambWeight) * color.xyz + SpecularComponent).xyz, color.w);

	if(resultColor.a<0.1)
		discard;

	//fog
	float distanceFromCameraToFrag = distance(vec4(u_camPosition, 1.0), vec4(v_posW, 1.0));
	float factor = clamp((distanceFromCameraToFrag - u_fogStart)/u_fogRange, 0.0, 1.0);


	gl_FragColor = mix(resultColor, vec4 (u_fogColor, 1.0), factor);
}
