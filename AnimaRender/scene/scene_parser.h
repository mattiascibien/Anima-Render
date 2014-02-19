#pragma once

#include "Camera.h"
#include "Object.h"
#include "Transform.h"
#include "Light.h"


#include <fstream>
#include <exception>

#define CANT_OPEN_FILE "Can't open file"
#define CANT_READ_FILE "Error reading file"
#define WRONG_SYNTAX "Syntax Error"
#define FILE_MISSING "One file specified in the scene is missing"
#define EXCEED_LIGHTS "A Scene can have only up to 8 lights"
#define EXCEED_TEXTURE_LIMITS "Texture index can only be between 0 and 7"

class ParseException: public exception
{
public:
	ParseException()
	{
		this->error = "ParseException";
	}
	ParseException(string error)
	{
		this->error = error;
	}

	virtual const char* what() const throw()
	{
		return error.c_str();
	}
private:
	string error;
};

Camera parseCamera(ifstream &fstream, std::string curDir);

Transform parseTransform(ifstream &fstream, std::string curDir, int lightCount);

Object parseObject(ifstream &fstream, std::string curDir);

Light parseLight(ifstream &fstream);

string getKeyword(ifstream &fstream);

void skipComment(ifstream &fstream);

void checkOpenBracket(ifstream &fstream);
