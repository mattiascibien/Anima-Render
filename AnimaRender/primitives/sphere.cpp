#include "sphere.h"


#include <boost\math\constants\constants.hpp>

void make_sphere(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &stCoordinates, std::vector<GLushort> &elements, int rings, int sectors)
{
	int radius = 1;

	float const R = 1.0f / (float) (rings - 1);
	float const S = 1.0f / (float) (sectors - 1);
	int r, s;

	vertices.resize(rings * sectors);
	normals.resize(rings * sectors);
	stCoordinates.resize(rings * sectors);
	std::vector<glm::vec3>::iterator v = vertices.begin();
	std::vector<glm::vec3>::iterator n = normals.begin();
	std::vector<glm::vec2>::iterator t = stCoordinates.begin();
	for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
		float const y = sin(-boost::math::float_constants::half_pi + boost::math::float_constants::pi * r * R);
		float const x = cos(2 * boost::math::float_constants::pi * s * S) * sin(boost::math::float_constants::pi * r * R);
		float const z = sin(2 * boost::math::float_constants::pi * s * S) * sin(boost::math::float_constants::pi * r * R);

		*t++ = glm::vec2(s*S, r*R);

		*v++ = glm::vec3(x * radius, y * radius, z * radius);

		*n++ = glm::vec3(x, y, z);
	}

	elements.resize(rings * sectors * 6);
	std::vector<GLushort>::iterator i = elements.begin();
	for (r = 0; r < rings - 1; r++) for (s = 0; s < sectors - 1; s++) {
		*i++ = r * sectors + s; //0		
		*i++ = (r + 1) * sectors + (s + 1); //2
		*i++ = r * sectors + (s + 1); //1
		*i++ = r * sectors + s; //0
		*i++ = (r + 1) * sectors + s; //3
		*i++ = (r + 1) * sectors + (s + 1); //2
	}
}