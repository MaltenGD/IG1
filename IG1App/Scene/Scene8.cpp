#include "Scene8.h"
#include "Entity/Sphere.h"
#include "Droid.h"
void Scene8::init()
{
	//// OpenGL basic setting
	//glClearColor(0, 0, 0, 1.0); // background color (alpha=1 -> opaque)
	//glEnable(GL_DEPTH_TEST);          // enable Depth test

	opaque_gObjects.push_back(new RGBAxes(400.0));
	Sphere* sphere = new Sphere(200,30,30);
	sphere->setColor(normalize(glm::vec4(171, 33, 72, 1)));
	Droid* droid = new Droid(50);
	glm::mat4 m = droid->modelMat();
	m = glm::translate<float>(m,glm::vec3(0,250,0));
	droid->setModelMat(m);
	opaque_gObjects.push_back(sphere);
	opaque_gObjects.push_back(droid);
}
