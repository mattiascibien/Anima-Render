uniform int NUMBER_OF_LIGHTS;

#define MAX_LIGHTS 8

varying vec3 normal;
varying vec3 lightvector[MAX_LIGHTS];
varying vec3 halfvector[MAX_LIGHTS];

void main()
{
	gl_Position = gl_ModelViewMatrix * gl_Vertex;
	vec3 viewvector = normalize(-gl_Position.xyz);
	normal = gl_NormalMatrix*gl_Normal;

	for(int i=0; i<NUMBER_OF_LIGHTS; i++)
	{
		lightvector[i] = normalize(gl_LightSource[i].position.xyz - gl_Position.xyz);
		halfvector[i] = normalize(viewvector + lightvector[i]);
	}
	gl_Position = gl_ProjectionMatrix * gl_Position;
}