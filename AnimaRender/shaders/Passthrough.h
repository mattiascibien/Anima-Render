#pragma once

char *passthrough_vert = "#version 120 \n void main( ) { 	gl_Position = gl_Vertex; 	gl_TexCoord[0] = gl_MultiTexCoord0; }";
int passthrough_vert_count = 94;

char *passthrough_frag = "uniform sampler2D texture; void main() { 	gl_FragColor = texture2D( texture, gl_TexCoord[0].st ); }";
int passthrough_frag_count = 99;