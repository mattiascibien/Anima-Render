#include "Scene.h"

#include <fstream>
#include <string>
#include <list>

#include "scene_parser.h"

#include <GL\glew.h>
#include <algorithm>

#include <boost/filesystem.hpp>


//Ci serve per indicare la directory del file che stiamo parsando
//così da poter leggere scene anche se non sono nella cartella dell'eseguibile
std::string extractDirectory(const std::string& path )
{
	return path.substr( 0, path.find_last_of( '\\' ) +1 );
}

//Caricamento della scena da file
Scene* Scene::load(string fileName)
{
	int lightCount = 0;
	Scene *scene = new Scene();
	boost::filesystem::path scenePath = boost::filesystem::path(fileName).parent_path();
	ifstream fstream(fileName.c_str());

	if(fstream.good())
	{
		while(!fstream.eof())
		{
			string key = getKeyword(fstream);

			if(key.compare("Camera") == 0) //trovata una camera
			{
				Camera camera = parseCamera(fstream, scenePath);
				camera.initCamera();
				if(camera.make_resources() == 0)
				{
					throw ParseException(FILE_MISSING);
				}
				scene->addCamera(camera);
			}
			else if(key.compare("Transform") == 0) //trovata una trasformazione affine
			{
				Transform transform = parseTransform(fstream, scenePath, lightCount);
				scene->rootTransform.addChild(transform);
			}
			else if(key.compare("#") == 0) //commento, va ignorato
				skipComment(fstream);
			else
				throw ParseException(WRONG_SYNTAX);
		}
		
	}
	else
		throw ParseException(CANT_OPEN_FILE);

	return scene;
}

Scene::Scene()
{
	cameras = std::vector<Camera>();
	//Valore con cui accediamo al vettore delle camere per ottenere quella attiva.
	activeCamera = 0;
}

void Scene::addCamera(Camera camera)
{
	cameras.push_back(camera);
}

void Scene::previsitLights()
{
	glEnable(GL_LIGHTING);
	rootTransform.previsitLights();
}

void Scene::render()
{
	//Implementazione dell'algoritmo 2 per le superfici semitrasparenti.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	rootTransform.render(false);
}

//Vai alla camera precedente
void Scene::prevCamera()
{
	if(activeCamera == 0)
	{
		//Cicliamo le telecamere
		activeCamera = cameras.size() - 1;
	}
	else
	{
		activeCamera--;
	}
	glutPostRedisplay();
}

//Vai alla camera successiva
void Scene::nextCamera()
{
	if(activeCamera == cameras.size() - 1)
	{
		//Cicliamo le telecamere
		activeCamera = 0;
	}
	else
	{
		activeCamera++;
	}
	glutPostRedisplay();
}

//Ottiene un riferimento alla camera attuale.
//Se venisse passata per copia non si vedrebbero
//Modifiche quando si sposta la telecamera
Camera& Scene::getActiveCamera()
{
	return cameras[activeCamera];
}
