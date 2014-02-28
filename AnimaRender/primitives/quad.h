#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

void make_quad(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &stCoordinates, std::vector<GLushort> &elements);