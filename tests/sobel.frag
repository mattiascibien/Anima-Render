uniform sampler2D texture;
uniform float width;
uniform float height;

float step_w = 1.0/width;
float step_h = 1.0/height;

/*
const vec2 offset[9] = vec2[]( vec2(-step_w, -step_h), vec2(0.0, -step_h), vec2(step_w, -step_h), 
				vec2(-step_w, 0.0), vec2(0.0, 0.0), vec2(step_w, 0.0), 
				vec2(-step_w, step_h), vec2(0.0, step_h), vec2(step_w, step_h) );
*/

void main(void)
{
    float sample[9];
	 vec3 luminance_converter = vec3(0.2126, 0.7152, 0.0722);
	

/*

    for (int i = 0; i < 9; i++)
    {
        sample[i] = dot(texture2D(texture, 
                              gl_TexCoord[0].st + offset[i]).rgb, luminance_converter);
    }

*/

	sample[0] = dot(texture2D(texture, gl_TexCoord[0].st + vec2(-step_w, -step_h)).rgb, luminance_converter);
	sample[1] = dot(texture2D(texture, gl_TexCoord[0].st + vec2(0.0, -step_h)).rgb, luminance_converter);
	sample[2] = dot(texture2D(texture, gl_TexCoord[0].st + vec2(step_w, -step_h)).rgb, luminance_converter);
	sample[3] = dot(texture2D(texture, gl_TexCoord[0].st + vec2(-step_w, 0.0)).rgb, luminance_converter);
	sample[4] = dot(texture2D(texture, gl_TexCoord[0].st + vec2(0.0, 0.0)).rgb, luminance_converter);
	sample[5] = dot(texture2D(texture, gl_TexCoord[0].st + vec2(step_w, 0.0)).rgb, luminance_converter);
	sample[6] = dot(texture2D(texture, gl_TexCoord[0].st + vec2(-step_w, step_h)).rgb, luminance_converter);
	sample[7] = dot(texture2D(texture, gl_TexCoord[0].st + vec2(0.0, step_h)).rgb, luminance_converter);
	sample[8] = dot(texture2D(texture, gl_TexCoord[0].st + vec2(step_w, step_h)).rgb, luminance_converter);

//    -1 -2 -1       1 0 -1 
// H = 0  0  0   V = 2 0 -2
//     1  2  1       1 0 -1
//
// result = sqrt(H^2 + V^2)

    float horizEdge = sample[0] + (2.0*sample[1]) + sample[2] -
                     (sample[6] + (2.0*sample[7]) + sample[8]);

    float vertEdge = sample[0] + (2.0*sample[3]) + sample[5] -
                    (sample[2] + (2.0*sample[5]) + sample[8]);

    gl_FragColor.rgb = vec3(sqrt((horizEdge * horizEdge) + 
                            (vertEdge * vertEdge)));

	 gl_FragColor.a = 1.0;								
    
}

