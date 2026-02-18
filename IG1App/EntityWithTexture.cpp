#include "EntityWithTexture.h"
#include "TextureManager.h"
using namespace glm;

EntityWithTexture::EntityWithTexture(const char * shader, Texture* texture)
{
	mShader = Shader::get(shader);
    mTexture = texture;
    /*mTexture->load("../assets/images/baldosaC.png");*/
 
}
void EntityWithTexture::render(const glm::mat4& modelViewMat) const
{
    if (mMesh != nullptr && mShader != nullptr) {
        
        mat4 aMat = modelViewMat * mModelMat;

        mShader->use();
        upload(aMat);

        if (mTexture != nullptr)
        {

            mShader->setUniform("modulate", mModulate);
            mTexture->bind();
            mMesh->render();
            mTexture->unbind();
        }
        else  mMesh->render();
        

    }
}
