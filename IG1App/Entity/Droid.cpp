#include "Droid.h"
#include "SphereWithTexture.h"
#include "Cone.h"

Droid::Droid(GLdouble radius)
{
    body = new SphereWithTexture(radius, 10, 10, "../assets/images/container.jpg");

    float EYE_X_POS = radius/2;
    float EYE_Y_POS = radius;
    float EYE_Z_POS = EYE_X_POS + radius/5;

    float EYE_HEIGHT = radius / 2;
    float EYE_RADIUS = radius / 10;

    //Cuerpo
    Cone* head = new Cone(radius/2,radius,radius/2,10,40);
    glm::mat4 m = head->modelMat();
    m = glm::translate<float>(m,glm::vec3(0,radius,0));
    head->setColor(glm::vec4(1, 1, 0,1));
    head->setModelMat(m);


    //OJOS
    Cone* left = new Cone(EYE_HEIGHT, EYE_RADIUS, EYE_RADIUS, 10, 40);
    m = left->modelMat();
    m = glm::translate<float>(m, glm::vec3(-EYE_X_POS, EYE_Y_POS, EYE_Z_POS)); 
    m = glm::rotate<float>(m, glm::radians(90.0f), glm::vec3(1, 0, 0));
    left->setColor(glm::vec4(0, 1, 0, 1));
    left->setModelMat(m);

    // ALTURA, RADIO MENOR, RADIO MAYOR, NRIMS, NSAMPLES
    Cone* right = new Cone(EYE_HEIGHT, EYE_RADIUS, EYE_RADIUS, 10, 40);
    m = right->modelMat();
    m = glm::translate<float>(m, glm::vec3(EYE_X_POS, EYE_Y_POS, EYE_Z_POS)); 
    m = glm::rotate<float>(m, glm::radians(90.0f), glm::vec3(1, 0, 0));  
    right->setColor(glm::vec4(0, 1, 0, 1));
    right->setModelMat(m);

    addEntity(body, head, left, right);
}

void Droid::rotate() 
{
    body->setModelMat(glm::rotate<float>(body->modelMat(), glm::radians<float>(5), glm::vec3(1, 0, 0)));
}

void Droid::render(const glm::mat4& modelViewMat) const
{
    if (!gObjects.empty())
    {
        glm::mat4 aMat = modelViewMat * mModelMat;
        for (Abs_Entity* entity : gObjects)
        {
            entity->render(aMat);
            glm::vec4 lightPosition = aMat * light->getPosition();
            //light->setPosition(glm::vec3(lightPosition.x, lightPosition.y, lightPosition.z));
            light->setPosition(aMat * light->getPosition());
            Shader* shader = Shader::get("light");
            shader->use();
            light->upload(*Shader::get("light"),aMat);
        }
    }
}

Droid::~Droid()
{

}
