#include "Star3D.h"
#include "Mesh.h"
using namespace glm;
Star3D::Star3D(GLdouble re, GLuint np, GLdouble h, const char* texture): EntityWithTexture(texture)
{
	mMesh = Mesh::generateStar3DTexCor(re, np, h);
}

void Star3D::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr)
	{
		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();

		if (mTexture != nullptr)
		{
			mTexture->bind();   // delante

			mShader->setUniform("modulate", mModulate);
			upload(aMat);
			mMesh->render();

			glm::mat4 new_model = glm::scale(mModelMat, glm::vec3(1, 1, -1));

			aMat = modelViewMat * new_model;
			upload(aMat);
			mMesh->render();

			mTexture->unbind();
		}
		else mMesh->render();
	}
	//if (mMesh != nullptr)
	//{
	//	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//	mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
	//	mShader->use();
	//	//mShader->setUniform("color", mColor);
	//	upload(aMat);
	//	mMesh->render();
	//	
	//	glm::mat4 new_model = glm::scale(mModelMat, glm::vec3(1, 1, -1));
	//	aMat = modelViewMat * new_model;
	//	upload(aMat);
	//	mMesh->render();
	//}
}

void Star3D::update()
{
	mSelfAngleDeg += 1.0f;  // Grados por frame
	mModelMat = glm::mat4(1.0f);
	GLfloat rad = glm::radians(mSelfAngleDeg);
	mModelMat = glm::rotate<float>(mModelMat, glm::radians(mSelfAngleDeg), glm::vec3(0, 1.0, 0)); // El orden IMPORTA
	mModelMat = glm::rotate<float>(mModelMat, glm::radians(mSelfAngleDeg), glm::vec3(0, 0, 1.0));
	//mModelMat = glm::translate<float>(mModelMat, glm::vec3(0 ,0, 0));


	//mModelMat = glm::rotate<float>(mModelMat, glm::radians(mSelfAngleDeg), glm::vec3(0, 1, 0)); //LMAOOOOOO
}
