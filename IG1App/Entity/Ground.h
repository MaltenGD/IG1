#pragma once
#include "EntityWithTexture.h"
//#include "Entity.h"

class Ground : public EntityWithTexture
{
public:
    Ground(GLdouble length, const char* texture);
    Ground(GLdouble length, Texture* texture);
    //void render(const glm::mat4& modelViewMat) const override;
};

