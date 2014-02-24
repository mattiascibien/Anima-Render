#include "tesselated_sphere.h"


void addTriangle(std::vector<GLushort> &elements, GLuint i_v0, GLuint i_v1, GLuint i_v2)
{
	elements.push_back(i_v0);
	elements.push_back(i_v1);
	elements.push_back(i_v2);
}

void midpoint(GLdouble v0x, GLdouble v0y, GLdouble v0z, GLdouble v1x, GLdouble v1y, GLdouble v1z, GLdouble &midx, GLdouble &midy, GLdouble &midz)
{
	midx = (v0x + v1x) / 2.0;
	midy = (v0y + v1y) / 2.0;
	midz = (v0z + v1z) / 2.0;
}

void normalize(GLdouble &vx, GLdouble &vy, GLdouble &vz)
{
	float length = sqrtf(vx*vx + vy*vy + vz*vz);
	vx = vx / length;
	vy = vy / length;
	vz = vz / length;
}

GLuint addMidPoint(std::vector<GLfloat> &vertices, GLdouble v0x, GLdouble v0y, GLdouble v0z, GLdouble v1x, GLdouble v1y, GLdouble v1z)
{
	GLdouble midx, midy, midz;
	midpoint(v0x, v0y, v0z, v1x, v1y, v1z, midx, midy, midz);
	normalize(midx, midy, midz);
	vertices.push_back(midx);
	vertices.push_back(midy);
	vertices.push_back(midz);
	return (vertices.size() - 3);
}

void subdivide(std::vector<GLfloat> &vertices, std::vector<GLushort> &elements, int i, GLuint i_v0, GLuint i_v1, GLuint i_v2)
{
	//vertex 0
	GLdouble v0x = vertices[i_v0];
	GLdouble v0y = vertices[i_v0 + 1];
	GLdouble v0z = vertices[i_v0 + 2];
	//vertex 1
	GLdouble v1x = vertices[i_v1];
	GLdouble v1y = vertices[i_v1 + 1];
	GLdouble v1z = vertices[i_v1 + 2];
	//vertex 2
	double v2x = vertices[i_v2];
	double v2y = vertices[i_v2 + 1];
	double v2z = vertices[i_v2 + 2];
	// indices of new vertices
	GLuint i_v3 = addMidPoint(vertices, v1x, v1y, v1z, v0x, v0y, v0z);
	GLuint i_v4 = addMidPoint(vertices, v1x, v1y, v1z, v2x, v2y, v2z);
	GLuint i_v5 = addMidPoint(vertices, v2x, v2y, v2z, v0x, v0y, v0z);
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
static const GLfloat g_vertex_buffer_data[] = {
	1.0f, 0.0f, 0.0f,   // 0
	0.0f, 0.0f, 1.0f,   // 1
	-1.0f, 0.0f, 0.0f,   // 2
	0.0f, 0.0f, -1.0f,  // 3
	0.0f, 1.0f, 0.0f,   // 4
	0.0f, -1.0f, 0.0f    // 5
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
void make_tesselated_sphere(std::vector<GLfloat> &vertices, std::vector<GLfloat> &normals, std::vector<GLfloat> &stCoordinates, std::vector<GLushort> &elements, int tesselation_level)
{
	//populate initial icosahedron
	for (int i = 0; i < 18; i = i + 3)
	{
		vertices.push_back(g_vertex_buffer_data[i]),
		vertices.push_back(g_vertex_buffer_data[i + 1]),
		vertices.push_back(g_vertex_buffer_data[i + 2]);
	}

	for (int j = 0; j<24; j++)
		elements.push_back(g_element_buffer_data[j]);

	/* subdivision */
	for (int k = 0; k<tesselation_level; k++)
	{
		int n_indices = elements.size();
		// consider one triangle at a time
		for (int i = 0; i<n_indices; i = i + 3)
			subdivide(vertices, elements, i, elements[i], elements[i + 1], elements[i + 2]);
	}
}