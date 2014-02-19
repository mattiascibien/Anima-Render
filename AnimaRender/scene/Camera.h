#pragma once

#include "../data/Vector.h"

#include <iostream>
#include <string>


#include "../glfuncs.h"
#include <gl\glew.h>

class Camera
{
private:
	
	Vector position;
	Vector direction;
	Vector up;
	Vector left;
	Vector yAxis;
	float fovY;
	float matrix [3][3];
	
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
	void setPosition(Vector pos);
	void setPosition(float x, float y, float z);
	Vector getPosition();

	void setDirection(Vector dir);
	void setDirection(float x, float y, float z);
	Vector getDirection();

	void setUp(Vector up);
	void setUp(float x, float y, float z);
	Vector getUp();

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

	void MatrixCreateFromAxisAngle(Vector v, float angle);

	Vector vectorMatrixTransform(Vector v);

	Vector Cross(Vector left, Vector right);


	int make_resources();
};