#include "Cone.h"
#include "IndexMesh.h"
#include <iostream>
Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples) :ColorMaterialEntity()
{
    std::vector<glm::vec2 > profile;
    profile.reserve(nRings + 2);
    //profile.reserve(nRings);

    // r el base
    // R el de arriba
    GLdouble yChunk = h / (nRings);
    GLdouble xChunk = (R - r) / nRings;
    GLdouble high = h / 2;

    // La otra forma de hacer las tapas es con el disk y que el cono sea un compound entity
    int steps = 0;
    //profile.push_back(glm::vec2(0, -(h / 2)));
    for (int y = -(h / 2); y <= (h / 2); y += yChunk)
    {
        profile.push_back(glm::vec2(r + steps * xChunk, y));
        ++steps;
    }
    profile.push_back(glm::vec2(0, h / 2));


    // Esto es identico a lo de arriba excepto que parte desde la base, y va hacia arriba
    //for (int y = 0; y < h; y += yChunk)
    //{
    //    std::cout << r + steps * xChunk << std::endl;
    //    profile.push_back(glm::vec2(r + steps * xChunk, y));
    //    ++steps;
    //}

    mMesh = IndexMesh::generateByRevolution(profile,nSamples);
}
