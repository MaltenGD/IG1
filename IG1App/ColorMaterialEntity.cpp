#include "ColorMaterialEntity.h"

bool ColorMaterialEntity::mShowNormals = false;

ColorMaterialEntity::ColorMaterialEntity()
{
   /* glEnable(GL_LIGHTING);*/
    mShader = Shader::get("simple_light");
}

void ColorMaterialEntity::toggleShowNormals()
{
    ColorMaterialEntity::mShowNormals = !ColorMaterialEntity::mShowNormals;
}

void ColorMaterialEntity::render(const glm::mat4& modelViewMat) const
{
    if (mMesh != nullptr)
    {
        glm::mat4 aMat = modelViewMat * mModelMat;
        mShader->use();
        mShader->setUniform("color", mColor);
        upload(aMat);
        mMesh->render();

        if (ColorMaterialEntity::mShowNormals) {


        }
    }
}
