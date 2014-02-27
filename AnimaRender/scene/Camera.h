#pragma once

#include "../data/Vector.h"

#include <iostream>
#include <string>


#include "../glfuncs.h"
#include <gl\glew.h>

#include <glm/glm.hpp>

class Camera
{
private:
	
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;
	glm::vec3 left;
	glm::vec3 yAxis;
	float fovY;
	glm::mat3x3 matrix;
	
	//variabili di movimento
	int fmove;
	int lmove;
	int vmove;

	//variabili di rotazione
	int xOrigin;
	int yOrigin;
	int rollMove;
	
	float speed;
	float PiOver4;

	std::string screenEffect;

public:
	GLShaderData postprocessData;
	GLuint textureWidthUniformLocation;
	GLuint textureHeightUniformLocation;
	GLuint textureUniformLocation;
	Camera()
	{
		screenEffect = "";
	}
	void initCamera();
	void setPosition(glm::vec3 pos);
	void setPosition(float x, float y, float z);
	glm::vec3 getPosition();

	void setDirection(glm::vec3 dir);
	void setDirection(float x, float y, float z);
	glm::vec3 getDirection();

	void setUp(glm::vec3 up);
	void setUp(float x, float y, float z);
	glm::vec3 getUp();

	void setFovY(float fovy);
	float getFovY();

	// Camera rotation
	void setDeltaMove(float x);
	void setMouseMove(int x, int y);
	void resetMouseMove();

	void mouseMove(int x, int y);

	void setScreenEffect(std::string filename);
	std::string getScreenEffectFilename();

	// Camera move
	void setMoveAhead(int front);
	void setMoveLateral(int lat);
	void setMoveUp(int up);

	void cameraMove();

	void setCameraRoll(int rolling);

	void MatrixCreateFromAxisAngle(glm::vec3 v, float angle);

	glm::vec3 vectorMatrixTransform(glm::vec3 v);

	int make_resources();
};