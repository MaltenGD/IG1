#pragma once
#include "Entity.h"
class RGBCube :
    public EntityWithColors
{

private:
    GLint rotation{0};
    GLdouble lenght;

public:
    RGBCube(GLdouble Lenght);
    void update() override;
};

