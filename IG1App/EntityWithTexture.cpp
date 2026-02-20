#include "EntityWithTexture.h"
#include <string>
using namespace glm;

EntityWithTexture::EntityWithTexture(const char* texture,const char* shader) :
    mModulate(false),
    mTexture(nullptr)
{
    //mTexture = new Texture();
    //mTexture->load(texture);
	mShader = Shader::get(shader);
}

EntityWithTexture::EntityWithTexture(Texture* texture, const char* shader):
    mModulate(false),
    mTexture(texture)
{
    mShader = Shader::get(shader);
}

EntityWithTexture::~EntityWithTexture()
{
    delete mTexture;
}

void EntityWithTexture::setTexture(Texture* tex)
{
    mTexture = tex;
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
        else mMesh->render();

    }
}
