#include "Scene3.h"
#include "RGBCube.h"

void
Scene3::init()
{
	setGL(); // OpenGL settings

	opaque_gObjects.push_back(new RGBAxes(400.0));
	opaque_gObjects.push_back(new RGBCube(100));

	

}
