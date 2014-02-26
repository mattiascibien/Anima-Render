#include "quad.h"

GLfloat quad_vertices[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
};

GLfloat quad_normals[] = {
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
};

GLfloat quad_st[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f
};

GLushort quad_elements[] = { 0, 1, 2, 0, 2, 3 };

void make_quad(std::vector<GLfloat> &vertices, std::vector<GLfloat> &normals, std::vector<GLfloat> &stCoordinates, std::vector<GLushort> &elements)
{
	for (size_t i = 0; i < 12; i++)
	{
		vertices.push_back(quad_vertices[i]);
	}

	for (size_t i = 0; i < 12; i++)
	{
		normals.push_back(quad_normals[i]);
	}

	for (size_t i = 0; i < 8; i++)
	{
		stCoordinates.push_back(quad_st[i]);
	}
	
	for (size_t i = 0; i < 6; i++)
	{
		elements.push_back(quad_elements[i]);
	}
}