#include "Sphere.h"
#include "IndexMesh.h"
Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians) :ColorMaterialEntity()
{
    mMesh = IndexMesh::generateSphere(radius, nParallels, nMeridians);
}

Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians, glm::vec3 colour):ColorMaterialEntity(colour)
{
    mMesh = IndexMesh::generateSphere(radius, nParallels, nMeridians);
}
