#pragma once
#include "SingleColorEntity.h"
class Cube :
    public SingleColorEntity
{
public:
    Cube(GLdouble Lenght, glm::vec4 color = {0,0,0,1});
};

