#include "ColorMaterialEntity.h"
#include "IG1App.h"

ColorMaterialEntity::ColorMaterialEntity()
{
   /* glEnable(GL_LIGHTING);*/
    mShader = Shader::get("simple_light");

    lightDir = glm::vec4{ -1.0f,-1.5f,-1.25f,0 };
    //lightDir = glm::vec4(1.0f);
}

void ColorMaterialEntity::render(const glm::mat4& modelViewMat) const
{
    //const glm::mat4& viewMat = IG1App::s_ig1app.camera().viewMat();
    //const glm::vec4 view = glm::vec4(viewMat * lightDir);
    //mShader->setUniform("lightDir", view);
    //SingleColorEntity::render(viewMat);
    if (mMesh != nullptr)
    {
        const glm::mat4& viewMat = IG1App::s_ig1app.camera().viewMat();
        glm::mat4 aMat = viewMat * mModelMat; // glm matrix multiplication
        mShader->use();
        const glm::vec4 view = glm::vec4(viewMat * lightDir);
        mShader->setUniform("lightDir", view);
        mShader->setUniform("color", mColor);
        upload(viewMat);
        mMesh->render();
    }
}
