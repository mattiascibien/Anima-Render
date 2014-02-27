#include "Transform.h"

#include <GL\glew.h>


Transform::Transform()
{
	setTranslation(glm::fvec3(0.0f, 0.0f, 0.0f));
	setRotation(0, glm::fvec3(0.0f, 0.0f, 0.0f));
	setScale(glm::fvec3(1.0f, 1.0f, 1.0f));
	m_children = std::list<Transform>();
	m_objects = std::list<Object>();
	m_lights = std::list<Light>();
}

//Imposta il vettore di traslazione
void Transform::setTranslation(glm::fvec3 trans)
{
	m_tanslation = trans;
}

void Transform::setTranslation(float x, float y, float z)
{
	setTranslation(Vector(x, y, z));
}

//Angolo e asse di rotazione
void Transform::setRotation(float rotDeg, glm::fvec3 axis)
{
	m_rotDeg = rotDeg;
	m_rotAxis = axis;
}

void Transform::setRotation(float rotDeg, float x, float y, float z)
{
	setRotation(rotDeg, glm::fvec3(x, y, z));
}

//Imposta il vettore di scala
void Transform::setScale(glm::fvec3  scale)
{
	m_scale = scale;
}

void Transform::setScale(float x, float y, float z)
{
	setScale(glm::fvec3(x, y, z));
}

//Aggiunge una trasformazione come figlia
//A quest'ultima vengono concatenate quelle della
//Trasformazione madre in fase di rendering
void Transform::addChild(Transform trans)
{
	m_children.push_back(trans);
}

//Aggiunge un oggetto
void Transform::addObject(Object obj)
{
	m_objects.push_back(obj);
}

//Aggiunge una luce
void Transform::addLight(Light light)
{
	m_lights.push_back(light);
}


void Transform::previsitLights()
{
	glPushMatrix();
	glTranslatef(m_tanslation.x, m_tanslation.y, m_tanslation.z);
	glRotatef(m_rotDeg, m_rotAxis.x, m_rotAxis.y, m_rotAxis.z);
	glScalef(m_scale.x, m_scale.y, m_scale.z);

	std::list<Light>::iterator it;
	for ( it=m_lights.begin() ; it != m_lights.end(); it++ )
	{
		it->enableLight();
	}
	std::list<Transform>::iterator it2;
	//Esegui ricorsivamente il rendering delle trasformazioni figlie
	for ( it2=m_children.begin() ; it2 != m_children.end(); it2++ )
	{
		it2->previsitLights();
	}

	glPopMatrix();
}

void Transform::render(bool renderSemiTransparent)
{
	glPushMatrix();
	glTranslatef(m_tanslation.x, m_tanslation.y, m_tanslation.z);
	glRotatef(m_rotDeg, m_rotAxis.x, m_rotAxis.y, m_rotAxis.z);
	glScalef(m_scale.x, m_scale.y, m_scale.z);

	std::list<Transform>::iterator it;
	//Esegui ricorsivamente il rendering delle trasformazioni figlie
	for ( it=m_children.begin() ; it != m_children.end(); it++ )
	{
		it->render(renderSemiTransparent);
	}
	
	std::list<Object>::iterator it2;
	for ( it2=m_objects.begin() ; it2 != m_objects.end(); it2++ )
	{
			it2->render();
	}
	glPopMatrix();
}