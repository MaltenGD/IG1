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
	Droid* droid = new Droid(20);
	glm::mat4 m = droid->modelMat();
	m = glm::translate<float>(m,glm::vec3(0, SPHERE_RADIUS + DROID_RADIUS,0));
	droid->setModelMat(m);
	

	Orbit_node = new CompoundEntity();

	Rotate_node = new CompoundEntity();

	Orbit_node->addEntity(Rotate_node);

	Rotate_node->addEntity(droid);
	Orbit_node->addEntity(sphere);

	opaque_gObjects.push_back(Orbit_node);
}


void Scene8::rotate() {
	glm::mat4 modelMat = Rotate_node->modelMat();
	Rotate_node->setModelMat(glm::rotate(modelMat, glm::radians<float>(2), glm::vec3(0, 1, 0)));

}

void Scene8::orbit() {
	glm::mat4 modelMat = Orbit_node->modelMat();
	Orbit_node->setModelMat(glm::rotate(modelMat, glm::radians<float>(2), glm::vec3(1, 0, 0)));
}


