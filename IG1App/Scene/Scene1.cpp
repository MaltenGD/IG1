#include "Scene1.h"
#include "RegularPolygon.h"
#include "Light.h"
void
Scene1::init()
{
	setGL(); // OpenGL settings
	//DirLight dirLight;
	//dirLight.setAmb(glm::vec3(0.25, 0.25, 0.25));
	//dirLight.setDiff(glm::vec3(.6, .6, .6));
	//dirLight.setSpec(glm::vec3(0, 0.2, 0));
	//gLights.push_back(dirLight);
	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	opaque_gObjects.push_back(new RGBAxes(400.0));
	opaque_gObjects.push_back(new RegularPolygon(7, 200, { 1,0,1,1 }));
	opaque_gObjects.push_back(new RegularPolygon(696, 200, { 1,1,0,1 }));

}
