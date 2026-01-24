#include "SingleColorEntity.h"
using namespace glm;
//
//SingleColorEntity::SingleColorEntity(){
//	mShader = Shader::get("simple");
//}

SingleColorEntity::SingleColorEntity(glm::vec4 newColor) {

	setColor(newColor);
	mShader = Shader::get("simple");
}

void SingleColorEntity::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
	    mShader->setUniform("color", mColor);
		mShader->use();
		upload(aMat);
		mMesh->render();
	}

}

