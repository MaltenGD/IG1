#include "Scene4.h"
#include "Ground.h"
#include "BoxOutline.h"
#include "Star3D.h"
#include "GlassParapet.h"
#include "Photo.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

void
Scene4::init()
{
	setGL(); // OpenGL settings
	opaque_gObjects.push_back(new RGBAxes(400.0));

	Photo* foto = new Photo(50.0, 50.0);
 foto->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0, 10, 0)) *
		glm::rotate(glm::mat4(1.0f), glm::pi<float>() / 2, glm::vec3(1, 0, 0)));
	opaque_gObjects.push_back(foto);
	opaque_gObjects.push_back(new Ground(250, "../assets/images/baldosaC.png"));
 BoxOutline* boxOutline = new BoxOutline(100, "../assets/images/papelE.png", "../assets/images/container.jpg");
	boxOutline->moveTo({ 0, 50, 0 });
	boxOutline->moveTo({ -5, 0, 3 });
	boxOutline->moveTo({ 150, 10, -100 });
	opaque_gObjects.push_back(boxOutline);
	GlassParapet* glassParapet = new GlassParapet(500, "../assets/images/windowC.png", 128);
	glassParapet->rotate(glm::vec3(1, 0.25f, 1));
	translucid_gObjects.push_back(glassParapet);
 Star3D* star3D = new Star3D(35, 5, 20, "../assets/images/rueda.png");
	star3D->setPosition({ 150, 90, -100 });
	opaque_gObjects.push_back(star3D);

}
