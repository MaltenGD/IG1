#include "Scene4.h"
#include "Ground.h"
#include "Texture.h"
#include "BoxOutline.h"
#include "Star3D.h"
#include "GlassParapet.h"
void
Scene4::init() // ESCENA VACÍA
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	//Texture* tex = new Texture();
	//tex->load("../assets/images/baldosaC.png");
	gObjects.push_back(new RGBAxes(400.0));
	//gObjects.push_back(new Ground(400.0, "../assets/images/baldosaC.png"));
	//gObjects.push_back(new Ground(400.0, tex));
	//gObjects.push_back(new BoxOutline(200,"../assets/images/papelE.png", "../assets/images/container.jpg"));
	//gObjects.push_back(new Star3D(100, 8, 100,"../assets/texturas/rueda.png"));
	gObjects.push_back(new GlassParapet(100,"../assets/images/windowC.png"));
}

void Scene4::update()
{
	for (auto& entity : gObjects)
	{
		entity->update();
	}
}
