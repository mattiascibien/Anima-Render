#include "cube.h"

static const GLfloat box_vertex_buffer_data[] = {
	1.0f, -1.0f, 1.0f,  // 0
	1.0f, 1.0f, 1.0f,  // 1
	-1.0f, 1.0f, 1.0f,  // 2
	-1.0f, -1.0f, 1.0f,  // 3
	1.0f, -1.0f, -1.0f,  // 4
	1.0f, 1.0f, -1.0f,  // 5
	-1.0f, 1.0f, -1.0f,  // 6
	-1.0f, -1.0f, -1.0f   // 7
};

static const GLuint box_element_buffer_data[] = {
	0, 1, 2, 3,
	0, 4, 5, 1,
	1, 5, 6, 2,
	3, 2, 6, 7,
	3, 7, 4, 0,
	7, 6, 5, 4
};

// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
static const GLfloat box_st_buffer_data[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
};

void make_cube(std::vector<GLfloat> &vertices, std::vector<GLfloat> &normals, std::vector<GLfloat> &stCoordinates, std::vector<GLushort> &elements)
{
	for (size_t i = 0; i < 24; i++)
	{
		vertices.push_back(box_vertex_buffer_data[i]);
		normals.push_back(box_vertex_buffer_data[i]);
		elements.push_back(box_element_buffer_data[i]);
	}

	for (size_t i = 0; i < 72; i++)
	{
		stCoordinates.push_back(box_st_buffer_data[i]);
	}
}