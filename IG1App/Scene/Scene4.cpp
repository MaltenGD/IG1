#include "Scene4.h"
#include "Ground.h"

void
Scene4::init() // ESCENA VACÍA
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new Ground(400.0));


}
