#include "Scene10.h"
#include "Sphere.h"
#include "Torus.h"
void Scene10::init()
{
	setGL(); // OpenGL settings
	opaque_gObjects.push_back(new RGBAxes(400.0));

	Sphere* gold = new Sphere(100,40,40,glm::vec3(0,1,0));
	glm::mat4 modelMat = gold->modelMat();
	modelMat = glm::translate(modelMat, glm::vec3(200, 0, 0));
	gold->setModelMat(modelMat);
	opaque_gObjects.push_back(gold);

	Sphere* copper = new Sphere(100, 40, 40, glm::vec3(0, 1, 0));
	modelMat = copper->modelMat();
	modelMat = glm::translate(modelMat, glm::vec3(0, 0, 200));
	copper->setModelMat(modelMat);
	opaque_gObjects.push_back(copper);

	//opaque_gObjects.push_back(new RGBAxes(400.0));
	//Torus* torus = new Torus(100, 50);
	//torus->setColor(glm::vec4(0, 1, 0, 0));
	//opaque_gObjects.push_back(torus);
}