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

void make_cube(std::vector<GLfloat> &vertices, std::vector<GLfloat> &normals, std::vector<GLfloat> &stCoordinates, std::vector<GLushort> &elements)
{
	for (size_t i = 0; i < 24; i++)
	{
		vertices.push_back(box_vertex_buffer_data[i]);
		normals.push_back(box_vertex_buffer_data[i]);
		elements.push_back(box_element_buffer_data[i]);
		stCoordinates.push_back(0.0f);
	}
}