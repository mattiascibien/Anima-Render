#include "Light.h"

#include <gl\glew.h>

int Light::numberOfLights = 0;

Light::Light(int lightNumber)
{
	this->lightNumber = lightNumber;
	numberOfLights++;
	setPosition(0.0f, 0.0f, 0.0f, 0.0f);
	setIrradiance(1.0f, 1.0f, 1.0f);
}

void Light::setPosition(float x, float y, float z, float w)
{
	position = Vector(x, y, z, w);

}

void Light::getPositionVector(float vect[4])
{
	vect[0] = position.x;
	vect[1] = position.y;
	vect[2] = position.z;
	vect[3] = position.w;
}


int Light::getNumberOfLights()
{
	return numberOfLights;
}

void Light::setIrradiance(float r, float g, float b)
{
	irradianceR = r;
	irradianceG = g;
	irradianceB = b;
	GLfloat irr[4] = { r, g, b, 1.0};
	glLightfv(lightNumber, GL_AMBIENT,  irr);
	glLightfv(lightNumber, GL_DIFFUSE,  irr);
	glLightfv(lightNumber, GL_SPECULAR,  irr);
}