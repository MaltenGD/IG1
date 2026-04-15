#include "Torus.h"
#include <numbers>
#include <vector>

using namespace glm;

Torus::Torus(GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples)
{

    std::vector<vec2> profile;
    profile.reserve(nPoints + 1); // +1 para cerrar el circulo

    //Para la circunferencia
    float rotaciónPorPunto = 2.0f * std::numbers::pi_v<float> / nPoints; 

    for (GLuint k = 0; k <= nPoints; ++k) {
        float t = rotaciónPorPunto * k;

        float x = r * cos(t) + R;
        float y = r * sin(t);

        profile.emplace_back(x, y);
    }

    mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}