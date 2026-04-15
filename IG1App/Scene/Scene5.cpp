#include "Scene5.h"
#include "Torus.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

void Scene5::init()
{
    setGL(); // OpenGL settings


    Torus* torus = new Torus(2.0, 0.5, 40, 40);
    torus->setColor({ 0.0f, 0.8f, 0.2f, 1.0f });

    opaque_gObjects.push_back(torus);
}