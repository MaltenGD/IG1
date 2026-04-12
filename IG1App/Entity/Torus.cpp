#include "Torus.h"
#include "IndexMesh.h"
Torus::Torus(GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples)
{
    std::vector<glm::vec2> profiles(nPoints);

    constexpr GLdouble PI = glm::pi<GLdouble>();

    const GLdouble rotationFactor = 2 * PI / nPoints;

    GLdouble actualRotation = PI * 0.5;

    for (size_t i = 0; i < nPoints; ++i)
    {
        glm::vec2 point(r * glm::cos(actualRotation) + R, r * glm::sin(actualRotation));

        profiles.push_back(point);

        actualRotation += rotationFactor;
    }

    // Una cosa es la figura de revolucion, otra cosa es la figura de revolucion pero con mallas indexadas
    mMesh = IndexMesh::generateByRevolution(profiles,nSamples);
}
