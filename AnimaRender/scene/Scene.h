#include <vector>

#include "Camera.h"
#include "Transform.h"

class Scene
{
public:
	Camera& getActiveCamera();

	static Scene load(string fileName);
	void addCamera(Camera camera);

	void prevCamera();
	void nextCamera();

	void render();
	void previsitLights();



	//TODO: dovrebbe essere private
	Scene();

private:

	std::vector<Camera> cameras;
	int activeCamera;
	Transform rootTransform;
};