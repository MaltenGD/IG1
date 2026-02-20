#include "Star3D.h"

using namespace glm;
Star3D::Star3D(GLdouble radioExterior, GLuint numPuntas, GLdouble altura)
{
	mMesh = Mesh::generateStar3D(radioExterior, numPuntas, altura);
    mModelMat180X = glm::rotate<float>(mModelMat, glm::pi<float>(), glm::vec3(1, 0, 0));
}

void Star3D::render(const glm::mat4& modelViewMat) const
{
    if (mMesh != nullptr) {
        mat4 aMat = modelViewMat * mModelMat;
        mat4 aMat180X = modelViewMat * mModelMat180X;
        mShader->use();
        upload(aMat);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        mMesh->render();

        upload(aMat180X);
        mMesh->render();


        


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    }
}
