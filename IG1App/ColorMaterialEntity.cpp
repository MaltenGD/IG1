#include "ColorMaterialEntity.h"
#include "IG1App.h"
bool ColorMaterialEntity::mShowNormals = false;

ColorMaterialEntity::ColorMaterialEntity()
{
   /* glEnable(GL_LIGHTING);*/
    mShader = Shader::get("light");
    mNormalShader = Shader::get("normals");
    setColor(mColor);
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
        mMaterial.upload(*mShader);
        upload(aMat);
        mMesh->render();

        if (ColorMaterialEntity::mShowNormals) {
            mNormalShader->use();
            mMesh->render();
        }

    }
}

void ColorMaterialEntity::setColor(glm::vec4 color)
{
    mColor = color;
    mMaterial = Material(glm::vec3(mColor), 32.0f);
}
