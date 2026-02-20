#include "Scene4.h"
#include "Ground.h"
#include "Texture.h"

void
Scene4::init() // ESCENA VACÍA
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	Texture* tex = new Texture();
	tex->load("../assets/images/baldosaC.png");
	gObjects.push_back(new RGBAxes(400.0));
	//gObjects.push_back(new Ground(400.0, "../assets/images/baldosaC.png"));
	gObjects.push_back(new Ground(400.0, tex));


}
