#include "sphere.h"


#include <boost\math\constants\constants.hpp>

void make_sphere(std::vector<GLfloat> &vertices, std::vector<GLfloat> &normals, std::vector<GLfloat> &stCoordinates, std::vector<GLushort> &elements)
{
	//TODO: make them variable
	int rings = 30;
	int sectors = 30;
	int radius = 1;

	float const R = 1. / (float) (rings - 1);
	float const S = 1. / (float) (sectors - 1);
	int r, s;

	vertices.resize(rings * sectors * 3);
	normals.resize(rings * sectors * 3);
	stCoordinates.resize(rings * sectors * 2);
	std::vector<GLfloat>::iterator v = vertices.begin();
	std::vector<GLfloat>::iterator n = normals.begin();
	std::vector<GLfloat>::iterator t = stCoordinates.begin();
	for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
		float const y = sin(-boost::math::double_constants::half_pi + boost::math::double_constants::pi * r * R);
		float const x = cos(2 * boost::math::double_constants::pi * s * S) * sin(boost::math::double_constants::pi * r * R);
		float const z = sin(2 * boost::math::double_constants::pi * s * S) * sin(boost::math::double_constants::pi * r * R);

		*t++ = s*S;
		*t++ = r*R;

		*v++ = x * radius;
		*v++ = y * radius;
		*v++ = z * radius;

		*n++ = x;
		*n++ = y;
		*n++ = z;
	}

	elements.resize(rings * sectors * 6);
	std::vector<GLushort>::iterator i = elements.begin();
	for (r = 0; r < rings - 1; r++) for (s = 0; s < sectors - 1; s++) {
		*i++ = r * sectors + s;
		*i++ = r * sectors + (s + 1);
		*i++ = (r + 1) * sectors + s;
		*i++ = r * sectors + (s + 1);
		*i++ = (r + 1) * sectors + (s + 1);
		*i++ = (r + 1) * sectors + s;
	}
}