#include "Ground.h"
using namespace glm;

Ground::Ground(GLdouble length, const char* shader, Texture* texture) : EntityWithTexture(shader, texture)
{
   mMesh = Mesh::generateRectangleTexCor(length, length, 1, 1);
   mModelMat = glm::rotate<float>(glm::mat4(1.0f), glm::pi<float>() / 2, glm::vec3(1, 0, 0));
}
