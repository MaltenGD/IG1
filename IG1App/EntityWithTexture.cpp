#include "EntityWithTexture.h"
#include <string>
using namespace glm;

EntityWithTexture::EntityWithTexture(const char* texture,const char* shader) :
    mModulate(false),
    mTexture(new Texture())
{
    mTexture->load(std::string(texture));
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
        mShader->setUniform("modulate", mModulate);
        if (mTexture != nullptr)
        {
            mTexture->bind();
            mMesh->render();
            mTexture->unbind();
        }
        else mMesh->render();

    }
}
