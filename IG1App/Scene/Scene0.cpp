#include "Scene0.h"

void
Scene0::init() // ESCENA VACÍA
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	Scene::init();
	opaque_gObjects.push_back(new RGBAxes(400.0));
}