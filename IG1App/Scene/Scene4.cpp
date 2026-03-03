#include "Scene4.h"
#include "Ground.h"
#include "BoxOutline.h"
#include "Star3D.h"
#include "GlassParapet.h"
void
Scene4::init() // ESCENA VAC�A
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
	gObjects.push_back(new GlassParapet(200, "../assets/images/windowC.png", 128));
}

void Scene4::update()
{
	for (auto& entity : gObjects)
	{
		entity->update();
	}
}
