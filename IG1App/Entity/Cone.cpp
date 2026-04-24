#include "Cone.h"
#include "IndexMesh.h"
#include <iostream>
Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples) :ColorMaterialEntity()
{
    std::vector<glm::vec2 > profile;
    profile.reserve(nRings + 2);

    // r el base
    // R el de arriba
    GLdouble yChunk = h / (nRings);
    GLdouble xChunk = (R - r) / nRings;

    int steps = 0;
    for (int y = -(h / 2); y <= (h / 2); y += yChunk)
    {
        profile.push_back(glm::vec2(r + steps * xChunk, y));
        ++steps;
    }

    // Si R == r, es un cilindro: no se añade ápice
    if (glm::abs(R - r) > 1e-6)
        profile.push_back(glm::vec2(0, h / 2));

    mMesh = IndexMesh::generateByRevolution(profile,nSamples);
}
