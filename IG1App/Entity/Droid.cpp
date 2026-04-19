#include "Droid.h"
#include "SphereWithTexture.h"
#include "Cone.h"
Droid::Droid(): CompoundEntity()
{
    SphereWithTexture* body = new SphereWithTexture(200, 10, 10, "../assets/images/container.jpg");
    addEntity(body);
    //Cone* head = new Cone();
}

Droid::Droid(GLdouble radius)
{
    SphereWithTexture* body = new SphereWithTexture(radius, 10, 10, "../assets/images/container.jpg");

    Cone* head = new Cone(radius/2,radius,radius/2,10,40);
    glm::mat4 m = head->modelMat();
    m = glm::translate<float>(m,glm::vec3(0,radius,0));
    head->setColor(glm::vec4(1, 1, 0,1));
    head->setModelMat(m);

    Cone* left = new Cone(50, 10, 10, 10, 40);
    m = left->modelMat();
    m = glm::rotate<float>(m, glm::radians(90.0f), glm::vec3(1, 0, 0));
    m = glm::translate<float>(m,glm::vec3(-25,100,-100)); // ?????
    left->setColor(glm::vec4(0, 1, 0, 1));
    left->setModelMat(m);


    Cone* right = new Cone(50, 10, 10, 10, 40);
    m = right->modelMat();
    m = glm::rotate<float>(m, glm::radians(90.0f), glm::vec3(1, 0, 0));
    m = glm::translate<float>(m, glm::vec3(25, 100, -100)); // ?????
    right->setColor(glm::vec4(0, 1, 0, 1));
    right->setModelMat(m);

    addEntity(body, head, left, right);
}

Droid::~Droid()
{

}
