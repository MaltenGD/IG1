#include "Cone.h"
#include "IndexMesh.h"
#include <iostream>
Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples) :ColorMaterialEntity()
{
    std::vector<glm::vec2 > profile;
    profile.reserve(nRings);


    // r el base
    // R el de arriba
    GLdouble yChunk = h / nRings;
    GLdouble xChunk = (R - r) / nRings;

    GLdouble a = ((R * R) - (r * r)) / h;
    GLdouble b = ((R * R) + (r * r)) / 2;
    GLdouble y = h / 2;

    //for (int i = y; i >= -y; y -= chunk)
    //{
    //    std::cout << a * i + b << std::endl;
    //    profile.push_back(glm::vec2(a * i + b, i));
    //}
    int steps = 0;
    for (int y = 0; y < h; y += yChunk)
    {
        std::cout << r + steps * xChunk << std::endl;
        profile.push_back(glm::vec2(r + steps * xChunk, y));
        ++steps;
    }

    mMesh = IndexMesh::generateByRevolution(profile,nSamples);
}
