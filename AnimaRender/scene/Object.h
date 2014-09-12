#pragma once

#include "..\objloader\objLoader.h"
#include "..\glfuncs.h"

#include <string>
#include <map>

#include <vector>



#include <glm/glm.hpp>

using namespace std;

class Object
{
public:
	Object();
	int loadGeometry(string filename);
	void setTexture(int id, string name, string filename);
	void setMaterial(string filename);
	void addParameter(string key, float value);
	void addParameter(string key, glm::vec4 value);

	void render();
	int makeResources();
	string primitiveKind;
	bool textured;

	void computeTangentBasis();
private:
	objLoader* objectLoader;
	std::vector<glm::vec3> vertices;
	std::vector<GLushort> elements;
	std::vector<glm::vec2> stCoordinates;
	std::vector<glm::vec3> normals;

	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;

	std::string material;
	std::string textureNames[8];
	std::string textureFileNames[8];

	std::map<std::string, float> floatParameters;
	std::map<std::string, glm::vec4> vectorParameters;

	std::map<std::string, GLint> uniformLocations;

	GLint lightNumberLocation;

	GlData data;
	GLShaderData shaderData;
};