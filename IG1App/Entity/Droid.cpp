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


    glm::vec3 bellyPos = glm::vec3(0.0f, -radius * 0.9f, 0.0f);

    light = new SpotLight(bellyPos, 0);
    light->setDirection(glm::vec3(0, -1, 0));
    light->setCutoff(30.0f, 45.0f); 
    light->setAttenuation(1.0f, 0.09f, 0.032f);
    light->setAmb(glm::vec3(0.1f, 0.1f, 0.1f));
    light->setDiff(glm::vec3(1.0f, 1.0f, 1.0f));
    light->setSpec(glm::vec3(1.0f, 1.0f, 1.0f));
    light->setEnabled(false);

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

      
        glm::vec4 worldPos = mModelMat * glm::vec4(light->getPosition().x, light->getPosition().y, light->getPosition().z, 1.0f);
        glm::vec3 worldDir = glm::normalize(-glm::vec3(worldPos)); // apunta al centro
        glm::vec3 viewDir = glm::vec3(modelViewMat * glm::vec4(worldDir, 0.0f));
        light->setDirection(viewDir);
        glm::vec3 viewPos = glm::vec3(modelViewMat * worldPos);
        light->setPosition(viewPos); 


        if (light->enabled()) {
            Shader* shader = Shader::get("light");
            shader->use();
            light->upload(*shader, glm::mat4(1.0f));
        }

        for (Abs_Entity* entity : gObjects)
        {
            entity->render(aMat);
        }
    }
}

Droid::~Droid()
{
    delete light;
}
