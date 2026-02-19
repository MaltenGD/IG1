#pragma once
#include "EntityWithTexture.h"
//#include "Entity.h"

class Ground : public EntityWithTexture
{
public:
    Ground(GLdouble length, const char* shader);
    void render(const glm::mat4& modelViewMat) const override;
};

