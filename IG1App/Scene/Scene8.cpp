#include "Scene8.h"
#include "Entity/Sphere.h"
#include "Droid.h"
void Scene8::init()
{
	//// OpenGL basic setting
	//glClearColor(0, 0, 0, 1.0); // background color (alpha=1 -> opaque)
	//glEnable(GL_DEPTH_TEST);          // enable Depth test

	float SPHERE_RADIUS = 200;
	float DROID_RADIUS = 20;

	opaque_gObjects.push_back(new RGBAxes(400.0));
	Sphere* sphere = new Sphere(SPHERE_RADIUS,30,30);
	sphere->setColor(glm::vec4(171.0f/255, 33.0f / 255, 72.0f / 255, 1));
	droid = new Droid(DROID_RADIUS);
	glm::mat4 m = droid->modelMat();
	m = glm::translate<float>(m,glm::vec3(0, SPHERE_RADIUS + DROID_RADIUS,0));
	droid->setModelMat(m);

	

	node = new CompoundEntity();
	node->addEntity(droid);
	//glm::mat4 m = node->modelMat();
	//m = glm::translate<float>(m, glm::vec3(0, SPHERE_RADIUS + DROID_RADIUS, 0));
	//node->setModelMat(m);

	opaque_gObjects.push_back(node);
	opaque_gObjects.push_back(sphere);
}


void Scene8::rotate() {
	glm::mat4 modelMat = node->modelMat();
	node->setModelMat(glm::rotate(modelMat, glm::radians<float>(2), glm::vec3(0, 1, 0)));

}

void Scene8::orbit() {
	glm::mat4 modelMat = node->modelMat();
	node->setModelMat(glm::rotate(modelMat, glm::radians<float>(2), glm::vec3(1, 0, 0)));
	droid->rotate();
}