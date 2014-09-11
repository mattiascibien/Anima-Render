#include "quad.h"

glm::vec3 quad_vertices[] = {
	glm::vec3(-1.0f, -1.0f, 0.0f),
	glm::vec3(1.0f, -1.0f, 0.0f),
	glm::vec3(1.0f, 1.0f, 0.0f),
	glm::vec3(-1.0f, 1.0f, 0.0f),
};

glm::vec3 quad_normals[] = {
	glm::vec3(0.0f, 0.0f, 1.0f),
};

glm::vec2 quad_st[] = {
	glm::vec2(0.0f, 0.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(1.0f, 1.0f),
	glm::vec2(0.0f, 1.0f)
};

GLushort quad_elements[] = { 0, 1, 2, 0, 2, 3 };

void make_quad(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &stCoordinates, std::vector<GLushort> &elements)
{
	for (size_t i = 0; i < 4; i++)
	{
		vertices.push_back(quad_vertices[i]);
		normals.push_back(quad_normals[0]);
	}
		


	for (size_t i = 0; i < 4; i++)
	{
		stCoordinates.push_back(quad_st[i]);
	}
	
	for (size_t i = 0; i < 6; i++)
	{
		elements.push_back(quad_elements[i]);
	}
}