#include "Disk.h"
#include <cassert>
#include "IndexMesh.h"
Disk::Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples)
{
    // R va desde el centro hasta el punto mas externo
    // r hasta el punto mas interno
    // hay nRings + 1 puntos en el profile
    assert(R>r);
    
    std::vector<glm::vec2> profile;
     //profile.assign(nRings, glm::vec2());
    profile.reserve(nRings);
     GLdouble chunk = (R - r) / (nRings);

    profile.push_back(glm::vec2(r, 0));
    for (int i = 1; i < nRings - 2;++i)
    {
        profile.push_back(glm::vec2(r + chunk * i, 0));
    }
    profile.push_back(glm::vec2(R, 0));

    mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}
