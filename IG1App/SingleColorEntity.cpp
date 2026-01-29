#include "SingleColorEntity.h"
using namespace glm;

SingleColorEntity::SingleColorEntity(glm::vec4 newColor) {

	mShader = Shader::get("simple");
	setColor(newColor);
}

void SingleColorEntity::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
	    mShader->setUniform("color", mColor);
		upload(aMat);
		mMesh->render();
	}

}

