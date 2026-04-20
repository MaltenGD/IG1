#include "ColorMaterialEntity.h"
#include "IG1App.h"
bool ColorMaterialEntity::mShowNormals = false;

ColorMaterialEntity::ColorMaterialEntity()
{
   /* glEnable(GL_LIGHTING);*/
    mShader = Shader::get("simple_light");
    mNormalShader = Shader::get("normals");
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
        //glm::mat4 viewMat = IG1App::s_ig1app.camera().viewMat();
       /* mShader->setUniform("lightDir", glm::normalize(viewMat * glm::vec4(-1,-1.5,-1.25,0));*/
        mShader->setUniform("color", mColor);
        upload(aMat);
        mMesh->render();

        if (ColorMaterialEntity::mShowNormals) {
            mNormalShader->use();
            mMesh->render();
        }

    }
}
