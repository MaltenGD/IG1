#include "Scene4.h"
#include "Ground.h"
#include "BoxOutline.h"
#include "Star3D.h"
#include "GlassParapet.h"
#include "Photo.h"
using namespace glm;

void
Scene4::init()
{
	setGL(); // OpenGL settings
	opaque_gObjects.push_back(new RGBAxes(400.0));

	Photo* foto = new Photo(50.0, 50.0);
	foto->moveTo({ 0, 10, 0 });
	opaque_gObjects.push_back(foto);
	opaque_gObjects.push_back(new Ground(250, "../assets/images/baldosaC.png"));
	opaque_gObjects.push_back(new BoxOutline(100,"../assets/images/papelE.png", "../assets/images/container.jpg"));
	GlassParapet* glassParapet = new GlassParapet(500, "../assets/images/windowC.png", 128);
	glassParapet->rotate(glm::vec3(1, 0.25f, 1));
	translucid_gObjects.push_back(glassParapet);
	opaque_gObjects.push_back(new Star3D(35, 5, 20, "../assets/images/rueda.png"));

}
