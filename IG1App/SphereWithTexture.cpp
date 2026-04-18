#include "SphereWithTexture.h"
#include "IndexMesh.h"
SphereWithTexture::SphereWithTexture(GLdouble radius, GLuint nParallel, GLuint nMeridians,const char* texture): EntityWithTexture(texture)
{

    //std::vector<glm::vec2> profiles;
    //profiles.reserve(nParallel);

    //constexpr GLdouble PI = glm::pi<GLdouble>();

    //const GLdouble rotationFactor = PI;

    //GLdouble actualRotation = PI * 3 / 4;

    //for (size_t i = 0; i <= nParallel; ++i)
    //{
    //    glm::vec2 point(radius * glm::cos(actualRotation), radius * glm::sin(actualRotation));

    //    profiles.push_back(point);

    //    actualRotation -= rotationFactor;
    //}

    mMesh = IndexMesh::generateSphere(radius,nParallel,nMeridians);
}
