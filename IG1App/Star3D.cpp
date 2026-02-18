#include "Star3D.h"

using namespace glm;
Star3D::Star3D(GLdouble radioExterior, GLuint numPuntas, GLdouble altura)
{
	mMesh = Mesh::generateStar3D(radioExterior, numPuntas, altura);
}

void Star3D::render(const glm::mat4& modelViewMat) const
{
    if (mMesh != nullptr) {
        mat4 aMat = modelViewMat * mModelMat;
        mShader->use();
        upload(aMat);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        mMesh->render();


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    }
}
