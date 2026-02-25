#include "Star3D.h"
#include "Mesh.h"
using namespace glm;
Star3D::Star3D(GLdouble re, GLuint np, GLdouble h)
{
	mMesh = Mesh::generateStar3D(re, np, h);
}

void Star3D::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr)
	{
		//glm::mat4 new_model = glm::scale(glm::mat4(1.0f), glm::vec3(0, 0, -1));
		//mModelMat = glm::scale<float>(mModelMat, glm::vec3(0, 0, -1));
		//mModelMat = mModelMat * new_model;
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("color", mColor);
		upload(aMat);
		mMesh->render();
		
		glm::mat4 new_model = glm::scale(mModelMat, glm::vec3(1, 1, -100));
		aMat = modelViewMat * new_model;
		upload(aMat);
		mMesh->render();


	}
}
