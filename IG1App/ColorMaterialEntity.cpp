#include "ColorMaterialEntity.h"

ColorMaterialEntity::ColorMaterialEntity()
{
   /* glEnable(GL_LIGHTING);*/
    mShader = Shader::get("simple_light");
}
