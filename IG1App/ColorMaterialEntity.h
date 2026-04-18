#ifndef _COLOR_MATERIAL_ENTITY_H
#define _COLOR_MATERIAL_ENTITY_H

#include "SingleColorEntity.h"
class ColorMaterialEntity : public SingleColorEntity
{
private:
    static bool mShowNormals;
protected:
    glm::vec4 lightDir;
public:
    ColorMaterialEntity();
    static void toggleShowNormals();
    void render(const glm::mat4& modelViewMat) const override;
};

#endif // !_COLOR_MATERIAL_ENTITY_H

