#include "cube.h"

static const GLfloat box_vertex_buffer_data[] = {
	// front
	-1.0, -1.0, 1.0,
	1.0, -1.0, 1.0,
	1.0, 1.0, 1.0,
	-1.0, 1.0, 1.0,
	// back
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, 1.0, -1.0,
	-1.0, 1.0, -1.0,
};

static const GLuint box_element_buffer_data[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// top
	3, 2, 6,
	6, 7, 3,
	// back
	7, 6, 5,
	5, 4, 7,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// left
	4, 0, 3,
	3, 7, 4,
	// right
	1, 5, 6,
	6, 2, 1,
};

static const GLfloat box_st_buffer_data[] = {
	1, 0,
	1, 1,
	0, 1,
	0, 0,
	1, 0,
	1, 1,
	0, 1,
	0, 0,
};



void make_cube(std::vector<GLfloat> &vertices, std::vector<GLfloat> &normals, std::vector<GLfloat> &stCoordinates, std::vector<GLushort> &elements)
{
	for (size_t i = 0; i < 24; i++)
	{
		vertices.push_back(box_vertex_buffer_data[i]);
		normals.push_back(box_vertex_buffer_data[i]);

	}

	for (size_t i = 0; i < 36; i++)
	{
		elements.push_back(box_element_buffer_data[i]);
	}

	for (size_t i = 0; i < 16; i++)
	{
		stCoordinates.push_back(box_st_buffer_data[i]);
	}
}