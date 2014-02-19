#pragma once

#include <list>

#include "../data/Vector.h"
#include "Object.h"
#include "Light.h"

class Transform
{
private:
	Vector m_tanslation;
	
	float m_rotDeg;
	Vector m_rotAxis;

	Vector m_scale;

	std::list<Transform> m_children;
	std::list<Light> m_lights;
	std::list<Object> m_objects;

public:
	Transform();
	void setTranslation(Vector trans);
	void setTranslation(float x, float y, float z);

	void setRotation(float rotDeg, Vector axis);
	void setRotation(float rotDeg, float x, float y, float z);

	void setScale(Vector scale);
	void setScale(float x, float y, float z);

	void addChild(Transform trans);
	void addObject(Object obj);
	void addLight(Light light);

	void previsitLights();
	void render(bool renderSemiTransparent);
};