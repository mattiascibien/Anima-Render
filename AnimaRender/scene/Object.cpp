#include "Object.h"

#include "../utils/util.h"
#include "../objloader/obj_parser.h"

#include "../primitives/sphere.h"
#include "../primitives/cube.h"

#include "Light.h"

#include <list>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

//I parametri di default vengono inizializzati nel costruttore
Object::Object()
{
	objectLoader = new objLoader();

	for(int i = 0; i < 8; i++)
	{
		textureFileNames[i] = "";
		data.textures[i] = -1; //Non inizializzata
	}
	textured = false;
	primitiveKind = "";
}

//Ritorna se il file specificato è un obj valido
int Object::loadGeometry(string filename)
{
	return objectLoader->load(filename.c_str());
}

//il nome del file da caricare con make_resources.
void Object::setTexture(int id, string name, string filename)
{
	textureNames[id] = name;
	textureFileNames[id] = filename;
}

//Imposta l'algoritmo di shading con cui effettuale il rendering dell'oggetto
void Object::setMaterial(string filename)
{
	material = filename;
}

void Object::addParameter(string key, float value)
{
	floatParameters.insert(pair<string,int>(key, value));
}

void Object::addParameter(string key, Vector value)
{
	vectorParameters.insert(pair<string,Vector>(key, value));
}

//Effettivo rendering dell'oggetto
void Object::render()
{
	glUseProgram(shaderData.program);

	//Uniform float
	for(std::map<std::string, float>::iterator it= floatParameters.begin(); it != floatParameters.end(); it++)
	{
		string name = it->first;

		glUniform1f(uniformLocations[name], it->second);
	}
	
	//Uniform vec4
	for(std::map<std::string, Vector>::iterator it= vectorParameters.begin(); it != vectorParameters.end(); it++)
	{
		string name = it->first;

		glUniform4f(uniformLocations[name], it->second.x, it->second.y, it->second.z, it->second.w);
	}

	glUniform1i(lightNumberLocation, Light::getNumberOfLights());

	
	//Uniform textures
	for(int i = 0; i < 8; i++)
	{
		if(data.textures[i] != -1)
		{
			glActiveTexture(GL_TEXTURE0+i);
			GLint location = glGetUniformLocation(shaderData.program, textureNames[i].c_str());
			glBindTexture(GL_TEXTURE_2D, data.textures[i]);
			glUniform1i(location, i);
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, data.vertex_buffer);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(
		3,
		GL_FLOAT,
		sizeof(GLfloat)*3,
		(void*)0
		);

	glBindBuffer(GL_ARRAY_BUFFER, data.normal_buffer);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(
		GL_FLOAT,
		0,
		(void*)0
		);

	if(textured)
	{
		glBindBuffer(GL_ARRAY_BUFFER, data.st_buffer);
		glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		//Indichiamo la texture da renderizzare.
		glTexCoordPointer(
			2,
			GL_FLOAT,
			sizeof(GLfloat)*2,
			(void*)0
			);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.element_buffer);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDrawElements(
		GL_TRIANGLES,
		elements.size(),
		GL_UNSIGNED_SHORT,
		(void*)0
		);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	if(textured)
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

//Creiamo i buffer OpenGL e le texture leggendo i dati dell'obj
int Object::makeResources()
{
	if (primitiveKind == "")
	{

		//Carichiamo 
		int elementCounter = 0;
		for (int fcount = 0; fcount < objectLoader->faceCount; fcount++)
		{
			obj_face *curFace = objectLoader->faceList[fcount];

			for (int vcount = 0; vcount < 3; vcount++)
			{
				obj_vector *currentVertex = objectLoader->vertexList[curFace->vertex_index[vcount]];
				for (int i = 0; i<3; i++) //Inseriamo i vertici nel buffer da bindare
				{
					vertices.push_back(currentVertex->e[i]);
				}
				if (objectLoader->textureCount > 0)
				{
					obj_vector *currentTexture = objectLoader->textureList[curFace->texture_index[vcount]];
					textured = true;
					for (int i = 0; i<2; i++) //Inserisce le coordinate di texture nel buffer che andremo a bindare successivamente
					{
						stCoordinates.push_back(currentTexture->e[i]);
					}
				}

				if (objectLoader->normalCount > 0)
				{
					obj_vector *currentNormal = objectLoader->normalList[curFace->normal_index[vcount]];
					for (int i = 0; i < 3; i++) //Inserisce le normali nel buffer
					{
						normals.push_back(currentNormal->e[i]);
					}
				}

				elements.push_back(elementCounter++); //Riempiamo l'element buffer con un ciclo per indicare che vogliamo caricare tutti i vertici
			}
		}
	}
	else
	{
		if (primitiveKind.find("sphere") == 0)
		{
			std::vector<std::string> values;
			boost::split(values, primitiveKind, boost::is_any_of(" "));

			int rings = 10;
			int sectors = 10;

			if (values.size() > 2)
			{
				rings = atoi(values.at(2).c_str());
			}

			if (values.size() > 1)
			{
				sectors = atoi(values.at(1).c_str());
			}

			make_sphere(vertices, normals, stCoordinates, elements, rings, sectors);
		}
		else if (primitiveKind.compare("cube") == 0)
		{
			make_cube(vertices, normals, stCoordinates, elements);
		}
	}
	

	data.vertex_buffer = make_buffer(
		GL_ARRAY_BUFFER,
		&vertices[0],
		vertices.size() * sizeof(GLfloat)
		);

	data.normal_buffer = make_buffer(
		GL_ARRAY_BUFFER,
		&normals[0],
		normals.size() * sizeof(GLfloat)
		);


	data.element_buffer = make_buffer(
		GL_ELEMENT_ARRAY_BUFFER,
		&elements[0],
		elements.size() * sizeof(GLushort)
		);

	if(textured)
	{
		data.st_buffer = make_buffer(
			GL_ARRAY_BUFFER,
			&stCoordinates[0],
			stCoordinates.size() * sizeof(GLfloat)
			);

		for(int i = 0; i < 8; i++)
		{
			if(textureFileNames[i].compare("") != 0)
			{
				data.textures[i] = make_texture(textureFileNames[i].c_str());
				if(data.textures[i] == 0) //Zero in caso di errore
					return 0;
			}
		}
	}

	if (primitiveKind == "")
	{
		//Objectloader non serve più in quanto abbiamo tutti i dati nei buffer dell'oggetto data.
		delete objectLoader;
	}

	string vertexShaderFileName = material + ".vert";
	string fragmentShaderFileName = material + ".frag";

	shaderData.vertex_shader = make_shader(GL_VERTEX_SHADER,vertexShaderFileName.c_str());
	if(shaderData.vertex_shader == 0)
	{
		return 0;
	}

	shaderData.fragment_shader = make_shader(GL_FRAGMENT_SHADER, fragmentShaderFileName.c_str());
	if(shaderData.fragment_shader == 0)
		return 0;

	shaderData.program = make_program(shaderData.vertex_shader, shaderData.fragment_shader);

	if(shaderData.program == 0)
		return 0;

	lightNumberLocation = glGetUniformLocation(shaderData.program, "NUMBER_OF_LIGHTS");

	for(std::map<std::string, float>::iterator it= floatParameters.begin(); it != floatParameters.end(); it++)
	{
		const char* name = it->first.c_str();
		GLint location = glGetUniformLocation(shaderData.program, name);
		uniformLocations.insert(pair<string,GLint>(name, location));
	}
	
	for(std::map<std::string, Vector>::iterator it= vectorParameters.begin(); it != vectorParameters.end(); it++)
	{
		const char* name = it->first.c_str();
		GLint location = glGetUniformLocation(shaderData.program, name);
		uniformLocations.insert(pair<string,GLint>(name, location));
	}
	
	return 1;
}