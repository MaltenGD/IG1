#include "Scene6.h"
#include "Entity/IndexedBox.h"
void Scene6::init()
{
	opaque_gObjects.push_back(new RGBAxes(400.0));
	IndexedBox* box = new IndexedBox(50);
	box->setColor(glm::vec4(0,1,0,0 ));
	opaque_gObjects.push_back(box);
}
