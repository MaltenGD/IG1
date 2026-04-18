#include "Scene5.h"
#include "Entity/Torus.h"
void Scene5::init()
{
    setGL(); // OpenGL settings
    opaque_gObjects.push_back(new RGBAxes(400.0));
    Torus* torus = new Torus(200, 100);
    torus->setColor(glm::vec4(0, 1, 0, 0));
    opaque_gObjects.push_back(torus);
}
