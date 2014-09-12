#include "scene_parser.h"

#include "..\utils\util.h"

#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

//Legge un numero in virgola mobile dal file
float readFloat(ifstream &fstream)
{
	float number;

	try
	{
		fstream >> number;
	}
	catch (exception)
	{
		throw ParseException(CANT_READ_FILE);
	}

	return number;
}

//Legge una stringa delimitata da "" dal file
string readString(ifstream &fstream)
{
	enum StringScanState {out, in, finish};

	StringScanState state = out;
	string str;
	char c = '\0';

	while(!fstream.eof() && state != finish)
	{
		try
		{
			fstream.get(c);
		}
		catch (exception)
		{
			throw ParseException(CANT_READ_FILE);
		}

		switch(state)
		{
		case out:
			if(c == '"' || c == '“' || c == '”') //su suggerimento esterno abbiamo incluso dei caratteri speciali per sicurezza
				state = in;
			else if(c != ' ' && c != '\t')
				throw ParseException(CANT_READ_FILE); 
			break;

		case in:
			if(c != '"' && c != '“' && c != '”')
				str += c;
			else
				state = finish;
		}
	}

	if(state != finish)
		throw ParseException(WRONG_SYNTAX);

	return str;
}

//Parsa le sezioni camera del file
Camera parseCamera(ifstream &fstream, boost::filesystem::path curPath)
{
	Camera camera;
	
	checkOpenBracket(fstream);

	while(!fstream.eof())
	{
		string key = getKeyword(fstream);

		if(key.compare("position") == 0) //posizione
		{
			float x, y, z;
			x = readFloat(fstream);
			y = readFloat(fstream);
			z = readFloat(fstream);
			camera.setPosition(x, y, z);
		}
		else if(key.compare("direction") == 0)
		{
			float x, y, z;
			x = readFloat(fstream);
			y = readFloat(fstream);
			z = readFloat(fstream);
			camera.setDirection(x, y, z);
		}
		else if(key.compare("up") == 0) 
		{
			float x, y, z;
			x = readFloat(fstream);
			y = readFloat(fstream);
			z = readFloat(fstream);
			camera.setUp(x, y, z);
		}
		else if(key.compare("FOVy") == 0) 
		{
			float fovy = readFloat(fstream);
			camera.setFovY(fovy);
		}
		else if(key.compare("screenEffect") == 0) 
		{
			string filename = readString(fstream);
			boost::filesystem::path pathFile = curPath / boost::filesystem::path(filename);
			filename = pathFile.string();
			camera.setScreenEffect(filename);			
		}
		else if(key.compare("#") == 0) 
			skipComment(fstream);

		else if(key.compare("}") == 0) 
			break;

		else
			throw ParseException(WRONG_SYNTAX);
	}

	return camera;
}

Transform parseTransform(ifstream &fstream, boost::filesystem::path curPath, int lightCount)
{
	Transform transform;
	checkOpenBracket(fstream);

	while(!fstream.eof())
	{
		string key = getKeyword(fstream);

		if(key.compare("translation") == 0) //traslazione
		{
			float x, y, z;
			x = readFloat(fstream);
			y = readFloat(fstream);
			z = readFloat(fstream);
			transform.setTranslation(x, y, z);
		}
		else if(key.compare("rotation") == 0) //rotazione
		{
			float angle, x, y, z;
			angle = readFloat(fstream);
			x = readFloat(fstream);
			y = readFloat(fstream);
			z = readFloat(fstream);
			transform.setRotation(angle, x, y, z);
		}
		else if(key.compare("scale") == 0) //scala
		{
			float x, y, z;
			x = readFloat(fstream);
			y = readFloat(fstream);
			z = readFloat(fstream);
			transform.setScale(x, y, z);
		}
		else if(key.compare("Transform") == 0) //sotto trasformazione
		{
			Transform subTransform = parseTransform(fstream, curPath, lightCount);
			transform.addChild(subTransform);
		}
		else if(key.compare("Object") == 0) //oggetto
		{
			Object object = parseObject(fstream, curPath);
			transform.addObject(object);
		}
		else if(key.compare("Light") == 0) //luce
		{
			Light light = parseLight(fstream);
			transform.addLight(light);
			lightCount++;
			if(lightCount > 8)
			{
				throw ParseException(EXCEED_LIGHTS);
			}
		}
		else if(key.compare("#") == 0) //commento che va ignorato
			skipComment(fstream);

		else if(key.compare("}") == 0) //fine della scena
			break;
		else
			throw ParseException(WRONG_SYNTAX);
	}

	return transform;
}

Light parseLight(ifstream &fstream)
{
	static int currentLight = GL_LIGHT0;
	Light light(currentLight);
	checkOpenBracket(fstream);
	while(!fstream.eof())
	{
		string key = getKeyword(fstream);
		if(key.compare("position") == 0)
		{
			float x, y, z, w;
			x = readFloat(fstream);
			y = readFloat(fstream);
			z = readFloat(fstream);
			w = readFloat(fstream);

			light.setPosition(x, y, z, w);
		}
		else if(key.compare("irradiance") == 0)
		{
			float r, g, b;
			r = readFloat(fstream);
			g = readFloat(fstream);
			b = readFloat(fstream);

			light.setIrradiance(r, g, b);
		}
		else if(key.compare("#") == 0) //commento che va ignorato
			skipComment(fstream);

		else if(key.compare("}") == 0) //fine della scena
			break;
		else
			throw ParseException(WRONG_SYNTAX);
	}
	currentLight++;
	return light;
}

bool tryGetVector(glm::vec4 &vect, string value)
{
	std::vector<std::string> numbers;
	boost::split(numbers, value, boost::is_any_of(","));
	if(numbers.size() == 4)
	{
		vect.x = (float)atof(numbers[0].c_str());
		vect.y = (float)atof(numbers[1].c_str());
		vect.z = (float)atof(numbers[2].c_str());
		vect.w = (float)atof(numbers[3].c_str());
		return true;
	}
	return false;
}

//Legge un oggetto e ne carica gli elementi
Object parseObject(ifstream &fstream, boost::filesystem::path curPath)
{
	Object object;
	checkOpenBracket(fstream);

	bool geometry = false;

	while(!fstream.eof())
	{
		string key = getKeyword(fstream);

		if (key.compare("primitive") == 0)
		{
			if (!geometry)
			{
				object.primitiveKind = readString(fstream);
				geometry = true;
			}
			else
			{
				throw ParseException(PRIMITIVE_OR_GEOMETRY);
			}
		}
		else if(key.compare("geometry") == 0)
		{
			if (!geometry)
			{
				string filename = readString(fstream);
				boost::filesystem::path pathFile = curPath / boost::filesystem::path(filename);
				filename = boost::filesystem::canonical(pathFile).string();
				if (object.loadGeometry(filename) != 1)
				{
					throw ParseException(FILE_MISSING);
				}
				geometry = true;
			}
			else
			{
				throw ParseException(PRIMITIVE_OR_GEOMETRY);
			}
		} 
		else if(key.compare("material") == 0)
		{
			string filename = readString(fstream);
			boost::filesystem::path pathFile = curPath / boost::filesystem::path(filename);
			filename = pathFile.string();
			
			object.setMaterial(filename);
		}
		else if (key.compare("textured") == 0)
		{
			string value = readString(fstream);
			if (value.compare("true") == 0)
			{
				object.textured = true;
			}
		}
		else if(key.compare("params") == 0)
		{
			string params = readString(fstream);
			std::vector<std::string> keyValuePairs;
			boost::split(keyValuePairs, params, boost::is_any_of(";"));

			for(unsigned int i=0; i<keyValuePairs.size(); ++i)
			{
				//Un po' hackereccia ma funziona.
				glm::vec4 value;
				std::vector<std::string> currentKeyValuePair;
				boost::split(currentKeyValuePair, keyValuePairs[i], boost::is_any_of("="));
				if(tryGetVector(value, currentKeyValuePair[1])) //E' un vettore
				{
					object.addParameter(currentKeyValuePair[0], value); 
				}
				else //E' un float
				{
					object.addParameter(currentKeyValuePair[0], (float)atof(currentKeyValuePair[1].c_str()));
				}
			}
		}
		else if (key.find("texture") != string::npos) //Controlliamo se contiene un comando texture#
		{
			string name;
			fstream >> name;
			string filename = readString(fstream);
			boost::filesystem::path pathFile = curPath / boost::filesystem::path(filename);
			filename = boost::filesystem::canonical(pathFile).string();
			int id = atoi(key.substr(key.size() -1).c_str()); //TODO: migliorare come viene estratto il numero
			if(id > 7)
			{
				throw ParseException(EXCEED_TEXTURE_LIMITS);
			}
			object.setTexture(id, name, filename); //Non viene ancora caricata in memoria
		} 
		else if(key.compare("#") == 0) //commento, va ignorato
				skipComment(fstream);
		else if(key.compare("}") == 0)
		{
			break;
		}
		else
			throw ParseException(WRONG_SYNTAX);
	}

	//Carica effettivamente l'oggetto e crea i buffer per OpenGL
	if(object.makeResources() != 1)
	{
		throw ParseException("Object resources cannot be created");
	}
	return object;
}

//legge una parola chiave
string getKeyword(ifstream &fstream)
{
	string keyword;

	try
	{
		fstream >> keyword;
	}
	catch (exception)
	{
		throw ParseException(CANT_READ_FILE);
	}

	return keyword;
}

//Ignora i commenti
void skipComment(ifstream &fstream)
{
	char c = '\0';
	while(c != '\n' && !fstream.eof())
	try
	{
		fstream.get(c);
	}
	catch (exception)
	{
		throw ParseException(CANT_READ_FILE);
	}
}

//Controlla se è presente una parentesi aperta
void checkOpenBracket(ifstream &fstream)
{
	string bracket;

	try
	{
		fstream >> bracket;
	}
	catch (exception)
	{
		throw ParseException(CANT_READ_FILE);
	}

	if(bracket.compare("{") != 0)
		throw ParseException(WRONG_SYNTAX);
}