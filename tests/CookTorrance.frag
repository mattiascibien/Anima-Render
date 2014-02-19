uniform int NUMBER_OF_LIGHTS;

#define MAX_LIGHTS 8

varying vec3 normal;
varying vec3 halfvector[MAX_LIGHTS];
varying vec3 lightvector[MAX_LIGHTS];
varying vec3 viewvector;

uniform vec4 Kd; // surface diffuse color
uniform vec4 Ks; // surface specular color: equal to R_F(0)
uniform vec4 Ka; // surface ambient color
uniform float m; // material roughness (average slope of microfacets)
uniform float s; // percentage of incoming light which is specularly reflected

#define PI 3.14159265	

// compute the geometry term
float G(float NdotH, float NdotV, float VdotH, float NdotL)
{
	float G1 = 2.0 * NdotH * NdotV / VdotH;
	float G2 = 2.0 * NdotH * NdotL / VdotH;
	return min( 1.0, min( G1, G2 ));
}

// compute Fresnel reflection term
vec3 R_F(float VdotH) {
	return Ks.xyz + (1.0 - Ks.xyz)*pow(1.0-VdotH, 5.0);
}

// compute the normal distribution function, based on Beckmann distribution
float Beckmann(float NdotH){
	float A = 1.0 / (pow(m,2.0)+pow(NdotH,4.0)*PI);
	float B = exp( - pow( tan(acos(NdotH)) , 2.0) / pow(m,2.0));
	return A*B;
}

void main()
{
	vec3 n = normalize( normal );  
	vec3 v = normalize( viewvector );
	vec3 finalColor = vec3(0.0, 0.0, 0.0);

	for(int i= 0; i< NUMBER_OF_LIGHTS; i++ )
	{  
		vec3  l         		= normalize(  lightvector[i] );  
		vec3  h          		= normalize( halfvector[i] );  
		float  NdotH    		= max(0.0, dot( n, h ));  
		float  VdotH     		= max(0.0, dot( v, h ));  
		float  NdotV 			= max(0.0, dot( n, v ));  
		float  NdotL 			= max(0.0, dot( n, l ));    
		// specular BRDF
		vec3 Specular = (Beckmann(NdotH) * G(NdotH, NdotV, VdotH, NdotL) * R_F(VdotH)) / ( NdotL* NdotV);
		// usiamo gl_LightSource.diffuse come EL
		finalColor += gl_LightSource[i].diffuse.xyz * NdotL * ((1.0-s)*Kd.xyz + s*Specular) + (gl_LightSource[i].ambient.xyz*Ka.xyz);
	}

	gl_FragColor = vec4(finalColor, 1.0);
}