#include "GlassParapet.h"
#include "Mesh.h"
using namespace glm;
GlassParapet::GlassParapet(GLdouble length, const char* texture, GLubyte alpha = 255) : EntityWithTexture(texture, alpha)
{
	mMesh = Mesh::generateBoxOutlineTexCor(length);
	mModelMat = glm::scale(mModelMat, glm::vec3(1, 0.25f, 1));

}

GlassParapet::~GlassParapet() {
	delete mTexture;
	mTexture = nullptr;
}

void GlassParapet::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr)
	{
		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();

		if (mTexture != nullptr)
		{
			glDepthMask(GL_FALSE);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glBlendFunc(GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR);

			mTexture->bind();   // delante

			mShader->setUniform("modulate", mModulate);
			upload(aMat);
			mMesh->render();

			mTexture->unbind();
			glDisable(GL_BLEND);
			glDepthMask(GL_TRUE);
		}
		else mMesh->render();
	}
}