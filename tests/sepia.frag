uniform sampler2D texture;

void main()
{
	vec3 original_color = texture2D( texture, gl_TexCoord[0].st ).rgb; 
	vec3 luminance_converter = vec3(0.2126, 0.7152, 0.0722);
	float luminance = dot(original_color, luminance_converter); 
	vec4 sepia_converter = vec4(0.191, -0.054,-0.221,0.0);
	gl_FragColor = luminance + sepia_converter;
}
