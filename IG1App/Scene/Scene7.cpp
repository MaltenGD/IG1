#include "Scene7.h"

void Scene7::init()
{
	setGL();
	opaque_gObjects.push_back(new RGBAxes(400.0));
}
