#include "Scene4.h"
#include "Ground.h"
#include "BoxOutline.h"
#include "Star3D.h"
#include "GlassParapet.h"
#include "Photo.h"
void
Scene4::init()
{
	setGL(); // OpenGL settings


	gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new Ground(500.0, "../assets/images/baldosaC.png"));
	gObjects.push_back(new BoxOutline(200,"../assets/images/papelE.png", "../assets/images/container.jpg"));
	gObjects.push_back(new GlassParapet(1000, "../assets/images/windowC.png", 128));
	gObjects.push_back(new Star3D(50, 5, 20, "../assets/images/rueda.png"));

	Photo* foto = new Photo(100.0, 100.0);
	gObjects.push_back(foto);
}

void Scene4::update()
{
	for (auto& entity : gObjects)
	{
		entity->update();
	}
}
