#include "Star3D.h"

using namespace glm;

Star3D::Star3D(GLdouble radioExterior, GLuint numPuntas, GLdouble altura, const char* texture) : EntityWithTexture(texture)
{
    mMesh = Mesh::generateStar3DTexCor(radioExterior, numPuntas, altura);
    glm::mat4 T = glm::translate(glm::mat4(1.0f), mCoordinates + glm::vec3(0,radioExterior,0)); // Para que no atraviese el suelo.
    mModelMat = T;
    mModelMat180X = T * glm::rotate(glm::mat4(1.0f), glm::pi<float>(), glm::vec3(1, 0, 0));
}

void Star3D::update()
{
    mAngle += 1.0f;
    glm::mat4 T = glm::translate(glm::mat4(1.0f), mCoordinates);
    glm::mat4 R = glm::rotate(glm::mat4(1.0f), glm::radians(mAngle), glm::vec3(0, 1, 0));
    mModelMat = T * R;
    mModelMat180X = T * R * glm::rotate(glm::mat4(1.0f), glm::pi<float>(), glm::vec3(1, 0, 0));
}

void Star3D::render(const glm::mat4& modelViewMat) const
{
    if (mMesh != nullptr) 
    {
        mat4 aMat = modelViewMat * mModelMat;
        mat4 aMat180X = modelViewMat * mModelMat180X;
        mTexture->bind();
        mShader->setUniform("modulate", mModulate);
        upload(aMat);

        mMesh->render();

        upload(aMat180X);

        mShader->setUniform("modulate", mModulate);
        mMesh->render();

        mTexture->unbind();





    } 
}