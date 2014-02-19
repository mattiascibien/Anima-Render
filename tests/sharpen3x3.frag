uniform sampler2D texture;
uniform float width;
uniform float height;

float step_w = 1.0/width;
float step_h = 1.0/height;

/* the version now commented should work, but it does not on Mac os X, due to a bug in the glsl implementation

#define KERNEL_SIZE 9

// Sharpen kernel
// -1 -1 -1
// -1 9 -1
// -1 -1 -1

const float kernel[KERNEL_SIZE]=float[](-1.0, -1.0, -1.0, -1.0, 9.0, -1.0, -1.0, -1.0, -1.0);
				
const vec2 offset[KERNEL_SIZE] = vec2[]( vec2(-step_w, -step_h), vec2(0.0, -step_h), vec2(step_w, -step_h), 
				vec2(-step_w, 0.0), vec2(0.0, 0.0), vec2(step_w, 0.0), 
				vec2(-step_w, step_h), vec2(0.0, step_h), vec2(step_w, step_h) );
				
void main(void)
{
   
   vec4 sum = vec4(0.0);
   
   for( int i=0; i<KERNEL_SIZE; i++ )
			sum += texture2D(texture, gl_TexCoord[0].st + offset[i]) * kernel[i];
   gl_FragColor = sum/16.0;
}

*/

void main(void)
{
   
   vec4 sum = vec4(0.0);
   
			sum += texture2D(texture, gl_TexCoord[0].st + vec2(-step_w, -step_h)) * -1.0;
			sum += texture2D(texture, gl_TexCoord[0].st + vec2(0.0, -step_h)) * -1.0;
			sum += texture2D(texture, gl_TexCoord[0].st + vec2(step_w, -step_h)) * -1.0;
			sum += texture2D(texture, gl_TexCoord[0].st + vec2(-step_w, 0.0)) * -1.0;
			sum += texture2D(texture, gl_TexCoord[0].st + vec2(0.0, 0.0))*9.0;
			sum += texture2D(texture, gl_TexCoord[0].st + vec2(step_w, 0.0))* -1.0;
			sum += texture2D(texture, gl_TexCoord[0].st + vec2(-step_w, step_h))* -1.0;
			sum += texture2D(texture, gl_TexCoord[0].st + vec2(0.0, step_h))* -1.0;
			sum += texture2D(texture, gl_TexCoord[0].st + vec2(step_w, step_h))* -1.0;
					
   gl_FragColor = sum;
}

