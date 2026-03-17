#include "EntityWithTexture.h"
#include "Texture.h"
#include <string>
using namespace glm;

EntityWithTexture::EntityWithTexture(const char* texture) :
    mModulate(false),
    mTexture(new Texture())
{
    mTexture->load(texture);
	mShader = Shader::get("texture");
}

EntityWithTexture::EntityWithTexture(const char* texture, GLubyte alpha):
mModulate(false),
mTexture(new Texture())
{
    mTexture->load(texture,alpha);
    mShader = Shader::get("texture");
}

EntityWithTexture::EntityWithTexture(Texture* texture, GLubyte alpha):
    mModulate(false),
    mTexture(texture)
{
    mShader = Shader::get("texture");
}

EntityWithTexture::EntityWithTexture(GLubyte alpha) :
    mModulate(false),
    mTexture(new Texture())
{
    mShader = Shader::get("texture");
}

EntityWithTexture::~EntityWithTexture()
{
    delete mTexture;
	mTexture = nullptr;
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
