#include "Cube.h"
using namespace glm;

Cube::Cube(GLdouble Lenght, glm::vec4 color) : SingleColorEntity(color)
{
	mMesh = Mesh::generateCube(Lenght);
}

void Cube::render(const glm::mat4& modelViewMat) const
{

	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		upload(aMat);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);   // Oculta la cara trasera para que los procesos que ocurran ahora solo afecten a la frontal

		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);  // PUNTOS
		mMesh->render();

		glCullFace(GL_BACK);  // Oculta la cara frontal para que los procesos que ocurran ahora solo afecten a la trasera

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);  // LINEAS
		mMesh->render();


		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_CULL_FACE);

	}


}
