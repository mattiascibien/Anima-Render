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
	
	glm::fvec3 position;
	glm::fvec3 direction;
	glm::fvec3 up;
	glm::fvec3 left;
	glm::fvec3 yAxis;
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
	void setPosition(glm::fvec3 pos);
	void setPosition(float x, float y, float z);
	glm::fvec3 getPosition();

	void setDirection(glm::fvec3 dir);
	void setDirection(float x, float y, float z);
	glm::fvec3 getDirection();

	void setUp(glm::fvec3 up);
	void setUp(float x, float y, float z);
	glm::fvec3 getUp();

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

	void MatrixCreateFromAxisAngle(glm::fvec3 v, float angle);

	glm::fvec3 vectorMatrixTransform(glm::fvec3 v);

	int make_resources();
};