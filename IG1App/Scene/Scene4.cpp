#include "Scene4.h"
#include "Ground.h"
#include "BoxOutline.h"

#include "Star3D.h"
void
Scene4::init() // ESCENA VACÍA
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene

	/*TextureManager* texManager = new TextureManager();*/
	gObjects.push_back(new RGBAxes(400.0));


	Texture* tex = new Texture();
	tex->load("../assets/images/baldosaC.png");
	gObjects.push_back(new Ground(350,"texture", tex));

	//Texture* outsideBoxTex = new Texture();
	//outsideBoxTex->load("../assets/images/papelE.png");
	//Texture* insideBoxTex = new Texture();
	//insideBoxTex->load("../assets/images/container.jpg");
	//gObjects.push_back(new BoxOutline(350, "texture", outsideBoxTex, insideBoxTex));

	//gObjects.push_back(new Star3D(50, 8, 50));



}
