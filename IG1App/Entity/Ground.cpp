#include "Ground.h"
using namespace glm;

Ground::Ground(GLdouble length, const char* shader) : EntityWithTexture(shader)
{
    mMesh = Mesh::createRGBRectangle(length, length);
    mModelMat = glm::rotate<float>(glm::mat4(1.0f), glm::pi<float>() / 2, glm::vec3(1, 0, 0));
}

void Ground::render(const glm::mat4& modelViewMat) const
{
    if (mMesh != nullptr) {
        mat4 aMat = modelViewMat * mModelMat;
        mShader->use();
        upload(aMat);

        //Para que todos los procesos de adelante se puedan tomar
        glEnable(GL_CULL_FACE);

        //TODO: preguntar a la profesora si es posible establecer PolygonMode para caras concretas (Front o back) para evitar render duplicado

        // PRIMERA PASADA: Se dibuja la cara trasera rellena
        glCullFace(GL_FRONT);   // Oculta la cara trasera para que los procesos que ocurran ahora solo afecten a la frontal
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Modo relleno
        mMesh->render();

        // SEGUNDA PASADA: Se dibuja la cara frontal con líneas
        glCullFace(GL_BACK);  // Oculta la cara frotnal para que los procesos que ocurran ahora solo afecten a la trasera
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Modo wireframe
        mMesh->render();

        // Se vuelve a dejar como estaba antes (se asume que el estado default sin culling)
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
