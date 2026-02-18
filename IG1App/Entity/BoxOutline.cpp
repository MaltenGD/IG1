#include "BoxOutline.h"
using namespace glm;

BoxOutline::BoxOutline(GLdouble Lenght, const char* shader, Texture* outsideTexture, Texture* insideTexture) : EntityWithTexture(shader, outsideTexture)
{
    insideTex = insideTexture;
	mMesh = Mesh::generateBoxOutlineTexCor(Lenght);
}

void BoxOutline::render(const glm::mat4& modelViewMat) const
{
    if (mMesh != nullptr && mShader != nullptr) {
        mat4 aMat = modelViewMat * mModelMat;
        mShader->use();
        upload(aMat);

        if (mTexture != nullptr) {
            mShader->setUniform("modulate", mModulate);

            glEnable(GL_CULL_FACE);

            glCullFace(GL_BACK); // Escondo las caras interiores para solo renderizar la exterior

            mTexture->bind(); //mTexture guarda la textura exterior de la caja
            mMesh->render();
            mTexture->unbind();

            
            glCullFace(GL_FRONT); // Ahora se hace justo lo contrario

            insideTex->bind();
            mMesh->render();
            insideTex->unbind();


            glDisable(GL_CULL_FACE);
        }
        else { // Por si no funciona la textura para que no crashee
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            mMesh->render();
        }

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
