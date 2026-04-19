#include "Scene7.h"
#include "SphereWithTexture.h"
#include "Disk.h"
#include "Cone.h"
#include "Droid.h"
void Scene7::init()
{
	setGL();
	opaque_gObjects.push_back(new RGBAxes(400.0));
	//opaque_gObjects.push_back(new SphereWithTexture(200, 10, 10, "../assets/images/container.jpg"));
	//opaque_gObjects.push_back(new Disk(250,0,10,10));
	//opaque_gObjects.push_back(new Cone(250,200,200,10,40));
	opaque_gObjects.push_back(new Droid(100));

	//Cone* left = new Cone(50, 10, 10, 10, 40);
	//glm::mat4 m;
	//m = left->modelMat();
	//m = glm::rotate<float>(m, glm::radians(90.0f), glm::vec3(1, 0, 0));
	//m = glm::translate<float>(m, glm::vec3(-25, 100, -100));
	//left->setColor(glm::vec4(0, 255, 0, 1));
	//left->setModelMat(m);

	//opaque_gObjects.push_back(left);
}
