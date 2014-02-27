#pragma once

#include <list>

#include "../data/Vector.h"
#include "Object.h"
#include "Light.h"

#include <glm/glm.hpp>

class Transform
{
private:
	glm::fvec3 m_tanslation;
	
	float m_rotDeg;
	glm::fvec3 m_rotAxis;

	glm::fvec3 m_scale;

	std::list<Transform> m_children;
	std::list<Light> m_lights;
	std::list<Object> m_objects;

public:
	Transform();
	void setTranslation(glm::fvec3 trans);
	void setTranslation(float x, float y, float z);

	void setRotation(float rotDeg, glm::fvec3 axis);
	void setRotation(float rotDeg, float x, float y, float z);

	void setScale(glm::fvec3 scale);
	void setScale(float x, float y, float z);

	void addChild(Transform trans);
	void addObject(Object obj);
	void addLight(Light light);

	void previsitLights();
	void render(bool renderSemiTransparent);
};