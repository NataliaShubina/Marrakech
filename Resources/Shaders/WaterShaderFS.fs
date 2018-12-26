precision mediump float;

//textures
uniform sampler2D u_textures2d[]; 
uniform samplerCube u_texturesCube[];
uniform float a_tFactor;

//lights
uniform vec3 u_lightColor[3];
uniform vec3 u_lightPositions[3];
uniform float u_specularPower;
uniform vec3 u_ambColor;
uniform float u_ambWeight;
uniform float u_depthDisp;
uniform vec3 u_depthColor;

uniform vec3 u_camPosition;
uniform float u_fogStart;
uniform float u_fogRange;
uniform vec3 u_fogColor;

//displacement
uniform float u_Time;
uniform float u_dMax;

//vectex data
varying vec3 v_normW;
varying vec3 v_posW;
varying vec3 v_binormW;
varying vec3 v_tgtW;
varying vec2 v_uv;

void main()
{

	vec3 DiffuseComponent;
	vec3 SpecularComponent;

	//displacement
	vec2 disp = texture2D(u_textures2d[2], vec2(v_uv.x - u_Time/5.0, v_uv.y)* a_tFactor).rg;

	vec2 offset = (2.0 * disp - 1.0) * u_dMax;
	vec2 new_uv = v_uv + offset;
	vec4 normal = texture2D(u_textures2d[1], new_uv * a_tFactor);

	float depthFactor = clamp(u_depthDisp * v_uv.y, 0.0, 1.0);

	offset = (2.0 * disp - 1.0) * depthFactor;
	new_uv = v_uv + offset;

	//bottom texture
	vec4 bottomColor = texture2D(u_textures2d[0], new_uv * a_tFactor);
	bottomColor = mix(bottomColor, vec4(u_depthColor, 1.0), depthFactor);


	mat3 mtxTBN = mat3(normalize(v_tgtW), normalize(v_binormW), normalize(v_normW));
	vec3 normalW = normalize(mtxTBN * (2.0 * normal.xyz - 1.0));

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

	vec4 refractionColor = vec4((mix(u_ambColor, DiffuseComponent, u_ambWeight) * bottomColor.xyz + SpecularComponent).xyz, bottomColor.w);


	//calculate reflection
	vec3 eyeDir = u_camPosition - v_posW;
	vec3 reflectDir = reflect(normalize(-eyeDir), normalize(normalW));  
	vec4 reflectColor = textureCube(u_texturesCube[0], reflectDir);

	//freshnel paramether
	float f = pow((1.0 - dot(normalize(normalW),normalize(eyeDir))), 1.0);

	float distanceFromCameraToFrag = distance(vec4(u_camPosition, 1.0), vec4(v_posW, 1.0));
	float factor = clamp((distanceFromCameraToFrag - u_fogStart)/u_fogRange, 0.0, 1.0);

	vec4 totalColor = mix(refractionColor, reflectColor, f);

	gl_FragColor = mix(totalColor, vec4 (u_fogColor, 1.0), factor);
}
