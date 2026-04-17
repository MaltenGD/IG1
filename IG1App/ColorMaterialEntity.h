#pragma once
#include "SingleColorEntity.h"
class ColorMaterialEntity : public SingleColorEntity
{
protected:
    glm::vec4 lightDir;
public:
    ColorMaterialEntity();

    void render(const glm::mat4& modelViewMat) const override;
};

