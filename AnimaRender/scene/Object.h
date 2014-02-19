#pragma once

#include "..\objloader\objLoader.h"
#include "..\glfuncs.h"

#include <string>
#include <map>

#include <vector>

#include "../data/Vector.h"

using namespace std;

class Object
{
public:
	Object();
	int loadGeometry(string filename);
	void setTexture(int id, string name, string filename);
	void setMaterial(string filename);
	void addParameter(string key, float value);
	void addParameter(string key, Vector value);

	void render();
	int makeResources();
	bool textured;
private:
	objLoader* objectLoader;
	std::vector<GLfloat> vertices;
	std::vector<GLushort> elements;
	std::vector<GLfloat> stCoordinates;
	std::vector<GLfloat> normals;

	std::string material;
	std::string textureNames[8];
	std::string textureFileNames[8];

	std::map<std::string, float> floatParameters;
	std::map<std::string, Vector> vectorParameters;

	std::map<std::string, GLint> uniformLocations;

	GLint lightNumberLocation;

	GlData data;
	GLShaderData shaderData;
};