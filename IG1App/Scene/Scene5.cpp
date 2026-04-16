#include "Scene5.h"
#include "Entity/Torus.h"
void Scene5::init()
{
    Torus* torus = new Torus(200, 50);
    opaque_gObjects.push_back(torus);
}
