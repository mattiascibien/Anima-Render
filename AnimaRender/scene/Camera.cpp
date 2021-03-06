#include "Camera.h"

#include <cmath>

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include <boost/filesystem.hpp>

//Inizializzazione della camera
void Camera::initCamera()
{
	fmove = 0;
	lmove = 0;
	vmove = 0;

	rollMove = 0;

	yAxis.x = 0.0f;
	yAxis.y = 1.0f;
	yAxis.z = 0.0f;
	
	speed = 1.0f;
	PiOver4 = 0.7853982;
}

void Camera::setPosition(glm::vec3 pos)
{
	position = pos;
}

void Camera::setPosition(float x, float y, float z)
{
	setPosition(glm::vec3(x, y, z));
}

void Camera::setDirection(glm::vec3 dir)
{
	direction = dir;
}

void Camera::setDirection(float x, float y, float z)
{
	setDirection(glm::vec3(x, y, z));
}

void Camera::setUp(glm::vec3 up)
{
	this->up= up;
}

void Camera::setUp(float x, float y, float z)
{
	setUp(glm::vec3(x, y, z));
}

void Camera::setFovY(float fovy)
{
	fovY = fovy;
}

float Camera::getFovY()
{
	return fovY;
}

glm::vec3 Camera::getPosition()
{
	return position;
}

glm::vec3 Camera::getDirection()
{
	glm::vec3 newDir;

	newDir.x = direction.x + position.x;
	newDir.y = direction.y + position.y;
	newDir.z = direction.z + position.z;

	return newDir;
}

glm::vec3 Camera::getUp()
{
	return up;
}

// Abilita il movimento 
void Camera::setMouseMove(int x, int y)
{
	xOrigin = x;
	yOrigin = y;
}

// Disabilita il movimento 
void Camera::resetMouseMove()
{
	xOrigin = -1;
	yOrigin = -1;
}

// Prende il movimento del mouse lungo x e y
void Camera::mouseMove(int x, int y)
{

	//Il movimento viene effettuato solo quando il pulsante
	//del mouse � premuto
    if ((xOrigin >= 0)&&(yOrigin >= 0)){
    
		// Camera Yaw
		MatrixCreateFromAxisAngle(up, (-PiOver4/150)*(x - xOrigin));
		setDirection(vectorMatrixTransform(direction));

		//Camera Pitch
		MatrixCreateFromAxisAngle(glm::cross(up,direction), (PiOver4/100)*(y - yOrigin));
		setDirection(vectorMatrixTransform(direction));
		setUp(vectorMatrixTransform(up));

		xOrigin = x;
		yOrigin = y;
	}
}

void Camera::cameraMove()
{
	//Calcola del vettore per il movimento laterale facendo il prodotto vettoriale tra
	//il vettore direzione e quello up
	glm::vec3 left = glm::cross(up, direction);

	// Camera Roll
	if(rollMove == -1)
	{
		MatrixCreateFromAxisAngle(direction, -PiOver4/200);
		setUp(vectorMatrixTransform(up));
	}

	if(rollMove == 1)
	{
		MatrixCreateFromAxisAngle(direction, PiOver4/200);
		setUp(vectorMatrixTransform(up));
	}

	// Movimento frontale
	if(fmove == 1){
		position.x += 0.01f * speed * direction.x;
		position.y += 0.01f * speed * direction.y;
		position.z += 0.01f * speed * direction.z;

	}else if(fmove == -1){
		
		position.x -= 0.01f * speed * direction.x;
		position.y -= 0.01f * speed * direction.y;
		position.z -= 0.01f * speed * direction.z;
	}

	// Movimento laterale
	if(lmove == 1){

		position.x -= 0.01f * speed * left.x;
		position.y -= 0.01f * speed * left.y;
		position.z -= 0.01f * speed * left.z;

	}else if(lmove == -1){
		
		position.x += 0.01f * speed * left.x;
		position.y += 0.01f * speed * left.y;
		position.z += 0.01f * speed * left.z;
	}

	// Movimento vericale
	if(vmove == 1){

		position.x += 0.01f * speed * up.x;
		position.y += 0.01f * speed * up.y;
		position.z += 0.01f * speed * up.z;

	}else if(vmove == -1){
		
		position.x -= 0.01f * speed * up.x;
		position.y -= 0.01f * speed * up.y;
		position.z -= 0.01f * speed * up.z;
	}
}

//Imposta movimento frontale
void Camera::setMoveAhead(int front)
{
	fmove = front;
}

//Imposta movimento laterale
void Camera::setMoveLateral(int lat)
{
	lmove = lat;
}

//Imposta moviemto vericale
void Camera::setMoveUp(int up)
{
	vmove = up;
}

//Imposta il roll della camera
void Camera::setCameraRoll(int rolling)
{
	rollMove = rolling;
}

//Crea una matrice di rotazione su un vettore arbitrario
void Camera::MatrixCreateFromAxisAngle(glm::vec3 v, float angle)
{
	matrix = glm::mat3x3(glm::rotate(angle, v));
}

//Trasforma un vettore in base alla matrice data
glm::vec3 Camera::vectorMatrixTransform(glm::vec3 v)
{
	return matrix * v;
}

void Camera::setScreenEffect(std::string fileName)
{
	this->screenEffect = boost::filesystem::canonical(fileName + ".frag").string();
}

std::string Camera::getScreenEffectFilename()
{
	return screenEffect;
}

int Camera::make_resources()
{
	//TODO: make passthrough included in memory instead from file
	if(screenEffect.compare("") == 0)
	{
		screenEffect = boost::filesystem::canonical("passthrough.frag").string();
	}

	postprocessData.vertex_shader = make_shader(GL_VERTEX_SHADER, "passthrough.vert");
	if(postprocessData.vertex_shader == 0)
		return 0;
	postprocessData.fragment_shader = make_shader(GL_FRAGMENT_SHADER, screenEffect.c_str());
	if(postprocessData.fragment_shader == 0)
		return 0;
	postprocessData.program = make_program(postprocessData.vertex_shader, postprocessData.fragment_shader);
	if(postprocessData.program == 0)
		return 0;

	textureUniformLocation = glGetUniformLocation(postprocessData.program, "texture");

	textureHeightUniformLocation = glGetUniformLocation(postprocessData.program, "height");
	textureWidthUniformLocation = glGetUniformLocation(postprocessData.program, "width");

	if(textureUniformLocation == -1)
		return 0;
	return 1;
}