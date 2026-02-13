#include "Ground.h"
using namespace glm;

Ground::Ground(GLdouble length, const char* shader) : EntityWithTexture(shader)
{
    mMesh = Mesh::createRGBRectangle(length, length);
   mModelMat = glm::rotate<float>(glm::mat4(1.0f), glm::pi<float>() / 2, glm::vec3(1, 0, 0));
}

void Ground::render(const glm::mat4& modelViewMat) const
{
    if (mMesh != nullptr) {
        mat4 aMat = modelViewMat * mModelMat;
        mShader->use();
        upload(aMat);
        mMesh->render();

        if (mTexture != nullptr)
        {
            mTexture->bind();
            mMesh->render();
            mTexture->unbind();
        }
    }
}
