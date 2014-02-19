uniform int NUMBER_OF_LIGHTS;

uniform sampler2D diffuseTexture;

#define MAX_LIGHTS 8

varying vec3 normal;
varying vec3 halfvector[MAX_LIGHTS];
varying vec3 lightvector[MAX_LIGHTS];

uniform vec4 ambient;
uniform vec4 specular;
uniform float shininess;

void main( void )
{
	vec3  n = normalize( normal );
	vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);

	for(int i=0; i<NUMBER_OF_LIGHTS; i++)
	{
		vec3  l = lightvector[i];
		vec3  h = halfvector[i];
		float fNDotL = max(0.0, dot( n, l )); 
   
		float fNDotH = max(0.0, dot( h, n ) );
      	
      	vec4 fvAmbient = gl_LightSource[i].ambient * ambient;
      	fvAmbient = clamp(fvAmbient, 0.0, 1.0);

   		vec4 fvDiffuse = fNDotL * gl_LightSource[i].diffuse * texture2D(diffuseTexture, gl_TexCoord[0].st); 
   		fvDiffuse = clamp(fvDiffuse, 0.0, 1.0);

   		vec4 fvSpecular = pow( fNDotH, shininess) * specular * gl_LightSource[i].specular;
   		fvSpecular = clamp(fvSpecular, 0.0, 1.0);

   		finalColor += fvAmbient + fvDiffuse + fvSpecular;
   }

	gl_FragColor = finalColor;      
}