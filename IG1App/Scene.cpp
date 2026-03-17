#include "Scene.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
Scene::~Scene()
{
	destroy();
	resetGL();
}

void
Scene::destroy()
{ // release memory and resources

	for (Abs_Entity* el : opaque_gObjects)
		delete el;

	opaque_gObjects.clear();

	for (Abs_Entity* el : translucid_gObjects)
		delete el;

	translucid_gObjects.clear();
}

void
Scene::load()
{
	for (Abs_Entity* obj : opaque_gObjects)
		obj->load();

	for (Abs_Entity* obj : translucid_gObjects)
		obj->load();
}

void
Scene::unload()
{
	for (Abs_Entity* obj : opaque_gObjects)
		obj->unload();

	for (Abs_Entity* obj : translucid_gObjects)
		obj->unload();
}

void
Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

void Scene::update() {
	for (Abs_Entity* entity : opaque_gObjects)
	{
		entity->update();
	}
	for (Abs_Entity* entity : translucid_gObjects)
	{
		entity->update();
	}
}


void
Scene::render(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : opaque_gObjects)
		el->render(cam.viewMat());

	for (Abs_Entity* el : translucid_gObjects)
		el->render(cam.viewMat());
}
