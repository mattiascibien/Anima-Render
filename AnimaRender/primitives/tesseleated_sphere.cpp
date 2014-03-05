#include "tesselated_sphere.h"


void addTriangle(std::vector<GLushort> &elements, GLuint i_v0, GLuint i_v1, GLuint i_v2)
{
	elements.push_back(i_v0);
	elements.push_back(i_v1);
	elements.push_back(i_v2);
}

glm::vec3 midpoint(glm::vec3 v0, glm::vec3 v1)
{
	return glm::vec3((v0.x + v1.x) / 2.0f, (v0.y + v1.y) / 2.0f, (v0.z + v1.z) / 2.0);
}


GLuint addMidPoint(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, glm::vec3 v0, glm::vec3 v1)
{
	glm::vec3 mid = midpoint(v0, v1);
	mid = glm::normalize(mid);
	vertices.push_back(mid);
	normals.push_back(mid);
	return (vertices.size() - 1);
}

void subdivide(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements, int i, GLuint i_v0, GLuint i_v1, GLuint i_v2)
{
	//vertex 0
	glm::vec3 v0 = vertices[i_v0];
	//vertex 1
	glm::vec3 v1 = vertices[i_v1];
	//vertex 2
	glm::vec3 v2 = vertices[i_v2];
	// indices of new vertices
	GLuint i_v3 = addMidPoint(vertices, normals, v1, v0);
	GLuint i_v5 = addMidPoint(vertices, normals, v2, v0);
	GLuint i_v4 = addMidPoint(vertices, normals, v1, v2);
	// first triangle replaces input one in indices vector
	elements[i] = i_v0;
	elements[i + 1] = i_v3;
	elements[i + 2] = i_v5;
	// others triangles go at the end of indices vector
	addTriangle(elements, i_v3, i_v1, i_v4);
	addTriangle(elements, i_v3, i_v4, i_v5);
	addTriangle(elements, i_v4, i_v2, i_v5);
}

//the starting icosahedron
static const glm::vec3 g_vertex_buffer_data[] = {
	glm::vec3(1.0f, 0.0f, 0.0f),   // 0
	glm::vec3(0.0f, 0.0f, 1.0f),   // 1
	glm::vec3(-1.0f, 0.0f, 0.0f),   // 2
	glm::vec3(0.0f, 0.0f, -1.0f),  // 3
	glm::vec3(0.0f, 1.0f, 0.0f),   // 4
	glm::vec3(0.0f, -1.0f, 0.0f)    // 5
};

static const GLuint g_element_buffer_data[] = {
	0, 4, 1,
	0, 1, 5,
	1, 4, 2,
	1, 2, 5,
	0, 3, 4,
	0, 5, 3,
	3, 2, 4,
	3, 5, 2
};

//code taken from: https://bitbucket.org/rranon/grafica3d-interattiva/src/6e38e0cf314b9c95b36e74734ef130591b879abb/drawing-geometry/sphere.cpp?at=default
void make_tesselated_sphere(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &stCoordinates, std::vector<GLushort> &elements, int tesselation_level)
{
	//populate initial icosahedron
	for (int i = 0; i < 6; i++)
	{
		vertices.push_back(g_vertex_buffer_data[i]);
		normals.push_back(g_vertex_buffer_data[i]);
	}

	for (int j = 0; j<24; j++)
		elements.push_back(g_element_buffer_data[j]);

	/* subdivision */
	for (int k = 0; k<tesselation_level; k++)
	{
		int n_indices = elements.size();
		// consider one triangle at a time
		for (int i = 0; i<n_indices; i = i + 3)
			subdivide(vertices, normals, elements, i, elements[i], elements[i + 1], elements[i + 2]);
	}
}