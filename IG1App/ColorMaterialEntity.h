#ifndef _COLOR_MATERIAL_ENTITY_H
#define _COLOR_MATERIAL_ENTITY_H

#include "EntityWithMaterial.h"

//class Shader;
class ColorMaterialEntity : public EntityWithMaterial
{
private:
    static bool mShowNormals;
    Shader* mNormalShader;
public:
    ColorMaterialEntity() = default;
    static void toggleShowNormals();
    void render(const glm::mat4& modelViewMat) const override;
    void setColor(glm::vec4 color = glm::vec4(0, 1, 0, 1));
};

#endif // !_COLOR_MATERIAL_ENTITY_H

