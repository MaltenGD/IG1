#include "RGBRectangle.h"
using namespace glm;

RGBRectangle::RGBRectangle(GLdouble w, GLdouble h)
{
	mMesh = Mesh::createRGBRectangle(w,h);
}

void RGBRectangle::render(const glm::mat4& modelViewMat) const
{
    if (mMesh != nullptr) {
        mat4 aMat = modelViewMat * mModelMat;
        mShader->use();
        upload(aMat);

        //Para que todos los procesos de adelante se puedan tomar
        glEnable(GL_CULL_FACE);

        //TODO: preguntar a la profesora si es posible establecer PolygonMode para caras concretas (Front o back) para evitar render duplicado

        // PRIMERA PASADA: Se dibuja la cara trasera rellena
        glCullFace(GL_BACK);  // Oculta la cara frotnal para que los procesos que ocurran ahora solo afecten a la trasera
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Modo relleno
        mMesh->render();

        // SEGUNDA PASADA: Se dibuja la cara frontal con líneas
        glCullFace(GL_FRONT);   // Oculta la cara trasera para que los procesos que ocurran ahora solo afecten a la frontal
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Modo wireframe
        mMesh->render();

        // Se vuelve a dejar como estaba antes (se asume que el estado default sin culling)
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
