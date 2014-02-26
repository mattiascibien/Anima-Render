#pragma once

#include <vector>
#include <GL/glew.h>

void make_tesselated_sphere(std::vector<GLfloat> &vertices, std::vector<GLfloat> &normals, std::vector<GLfloat> &stCoordinates, std::vector<GLushort> &elements, int tesselation_level);