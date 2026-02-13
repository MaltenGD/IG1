#include "EntityWithTexture.h"
using namespace glm;

EntityWithTexture::EntityWithTexture(const char * shader)
{
	mShader = Shader::get(shader);
}

void EntityWithTexture::render(const glm::mat4& modelViewMat) const
{
    if (mMesh != nullptr && mShader != nullptr) {
        
        mat4 aMat = modelViewMat * mModelMat;

        mShader->use();
        upload(aMat);

        if (mTexture != nullptr)
        {
            mTexture->bind();
            mMesh->render();
            mTexture->unbind();
        }
        else  mMesh->render();
        

    }
}
