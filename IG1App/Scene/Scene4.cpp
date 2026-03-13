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


	Photo* foto = new Photo(100.0, 100.0);
	gObjects.push_back(foto);
	gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new Ground(250, "../assets/images/baldosaC.png"));
	gObjects.push_back(new BoxOutline(200,"../assets/images/papelE.png", "../assets/images/container.jpg"));
	gObjects.push_back(new GlassParapet(500, "../assets/images/windowC.png", 128));
	gObjects.push_back(new Star3D(50, 5, 20, "../assets/images/rueda.png"));

}
