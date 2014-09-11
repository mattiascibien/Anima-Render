#include "cube.h"

static const glm::vec3 box_vertex_buffer_data[] = {
	// front
	glm::vec3(- 1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	// back
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f)
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

static const glm::vec2 box_st_buffer_data[] = {
	glm::vec2(1.0f, 0.0f),
	glm::vec2(1.0f, 1.0f),
	glm::vec2(0.0f, 1.0f),
	glm::vec2(0.0f, 0.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(1.0f, 1.0f),
	glm::vec2(0.0f, 1.0f),
	glm::vec2(0.0f, 0.0f),
};



void make_cube(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &stCoordinates, std::vector<GLushort> &elements)
{
	for (size_t i = 0; i < 8; i++)
	{
		vertices.push_back(box_vertex_buffer_data[i]);
		normals.push_back(box_vertex_buffer_data[i]);

	}

	for (size_t i = 0; i < 36; i++)
	{
		elements.push_back(box_element_buffer_data[i]);
	}

	for (size_t i = 0; i < 8; i++)
	{
		stCoordinates.push_back(box_st_buffer_data[i]);
	}
}