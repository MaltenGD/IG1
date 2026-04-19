#include "Scene7.h"
#include "SphereWithTexture.h"
#include "Disk.h"
#include "Cone.h"
void Scene7::init()
{
	setGL();
	opaque_gObjects.push_back(new RGBAxes(400.0));
	//opaque_gObjects.push_back(new SphereWithTexture(200, 10, 10, "../assets/images/container.jpg"));
	opaque_gObjects.push_back(new Disk(250,100,10,10));
	//opaque_gObjects.push_back(new Cone(250,100,200,10,40));
}
