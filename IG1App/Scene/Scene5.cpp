#include "Scene5.h"
#include "Entity/Torus.h"
void Scene5::init()
{
    Torus* torus = new Torus(100, 100);
    opaque_gObjects.push_back(torus);
}
