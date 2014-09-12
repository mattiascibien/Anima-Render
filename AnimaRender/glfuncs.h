#pragma once

#include <GL\glew.h>
#ifdef __APPLE__
#include <GLUT\glut.h>
#else
#include <Gl\glut.h>
#endif

#include "utils/util.h"

typedef struct {
	GLuint vertex_buffer, element_buffer;
	GLuint color_buffer;
	GLuint st_buffer;
	GLuint normal_buffer;
	GLuint tangent_buffer;
	GLuint bitangent_buffer;
	GLuint textures[8];

} GlData;

typedef struct{
	GLuint vertex_shader, fragment_shader, program;
} GLShaderData;

GLuint make_buffer(
	GLenum target,
	const void *buffer_data,
	GLsizei buffer_size
	);

GLuint make_texture(const char *filename);

void show_info_log(
    GLuint object,
    PFNGLGETSHADERIVPROC glGet__iv,
    PFNGLGETSHADERINFOLOGPROC glGet__InfoLog
);

GLuint make_shader(GLenum type, const char *filename);

GLuint make_program(GLuint vertex_shader, GLuint fragment_shader);