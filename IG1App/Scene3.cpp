#include "Scene3.h"
#include "Cube.h"

void
Scene3::init()
{
	setGL(); // OpenGL settings

	/*gObjects.push_back(new RGBAxes(400.0));*/
	gObjects.push_back(new Cube(100,{1, 1, 1, 1}));

	

}
