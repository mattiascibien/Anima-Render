uniform int NUMBER_OF_LIGHTS;

#define MAX_LIGHTS 8

varying vec3 normal;
varying vec3 lightvector[MAX_LIGHTS];
varying vec3 halfvector[MAX_LIGHTS];
varying vec3 viewvector;

void main()
{
	gl_Position = gl_ModelViewMatrix * gl_Vertex;
	viewvector = normalize(-gl_Position.xyz);
	normal = gl_NormalMatrix*gl_Normal;

	int i;
	for(i=0; i<MAX_LIGHTS; i++)
	{

		//Usare NUMBER_OF_LIGHTS nel for causava un problema di lvalue too complex
		if(i<NUMBER_OF_LIGHTS)
		{
			lightvector[i] = normalize(gl_LightSource[i].position.xyz - gl_Position.xyz);
			halfvector[i] = normalize(viewvector + lightvector[i]);
		}
	}
	gl_Position = gl_ProjectionMatrix * gl_Position;
}