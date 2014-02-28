#pragma once



#include <gl\glew.h>

#include <glm/glm.hpp>

class Light
{
private:
	glm::fvec4 position;
	float irradianceR;
	float irradianceG;
	float irradianceB;

	int lightNumber;
	static int numberOfLights;
public:
	Light(int lightNumber);
	void setPosition(float x, float y, float z, float w);
	void getPositionVector(float vect[4]);
	void setIrradiance(float r, float g, float b);
	static int getNumberOfLights();
	void enableLight()
	{
		GLfloat pos[4];
		getPositionVector(pos);
		glLightfv(lightNumber, GL_POSITION, pos);
	}
};