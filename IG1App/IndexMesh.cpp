#include "IndexMesh.h"
#include <algorithm>

using namespace std;
using namespace glm;

constexpr GLuint NONE = numeric_limits<GLuint>::max();

IndexMesh::IndexMesh()
{

}

void IndexMesh::draw() const
{
    glDrawElements(
        mPrimitive, // primitiva ( GL_TRIANGLES , etc.)
        vIndexes.size(), // número de índices
        GL_UNSIGNED_INT, // tipo de los índices
        nullptr // offset en el VBO de índices
    );
}


void IndexMesh::load()
{
    Mesh::load(); glBindVertexArray(mVAO);
    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        vIndexes.size() * sizeof(GLuint),
        vIndexes.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void IndexMesh::buildNormalVectors()
{
    // Se inicializa vNormals
    vNormals.assign(vVertices.size(), glm::vec3(0.0f, 0.0f, 0.0f));

    // Se recorre cada triangulo
    for (size_t i = 0; i < vIndexes.size(); i += 3)
    {
        GLuint i0 = vIndexes[i];
        GLuint i1 = vIndexes[i + 1];
        GLuint i2 = vIndexes[i + 2];

        // Normal de la cara
        glm::vec3 normal = normalize(cross(vVertices[i1] - vVertices[i0], vVertices[i2] - vVertices[i0]));

        // Se suma la normal de la cara a las normales de los vértices que forman la cara
        vNormals[i0] += normal;
        vNormals[i1] += normal;
        vNormals[i2] += normal;
    }

    for (size_t i = 0; i < vNormals.size();++i)
    {
        vNormals[i] = normalize(vNormals[i]);
    }
}

void IndexMesh::unload()
{
    Mesh::unload();

    if (mIBO != NONE)
    {
        glDeleteBuffers(1, &mIBO);
        mIBO = NONE;
    }
}

IndexMesh* IndexMesh::generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, GLfloat angleMax)
{
    IndexMesh* mesh = new IndexMesh;

    mesh->mPrimitive = GL_TRIANGLES;
    int tamPerfil = profile.size();
    mesh->vVertices.reserve(nSamples * tamPerfil);

    GLdouble theta1 = angleMax / nSamples;
    for (int i = 0; i <= nSamples; ++i) { // muestra i-¨¦sima
        GLdouble c = cos(i * theta1), s = sin(i * theta1);
        for (auto p : profile) // rota el perfil
            mesh->vVertices.emplace_back(p.x * c, p.y, -p.x * s);
    }

    for (int i = 0; i < nSamples; ++i) // caras i a i + 1
        for (int j = 0; j < tamPerfil - 1; ++j) { // una cara
            if (profile[j].x != 0.0) // tri¨¢ngulo inferior
                for (auto [s, t] : { std::pair{i, j}, {i, j + 1}, {i + 1, j} })
                    mesh->vIndexes.push_back(s * tamPerfil + t);
            if (profile[j + 1].x != 0.0) // tri¨¢ngulo superior
                for (auto [s, t] : { std::pair{i, j + 1}, {i + 1, j + 1}, {i + 1, j} })
                    mesh->vIndexes.push_back(s * tamPerfil + t);
        }
    mesh->mNumVertices = mesh->vVertices.size();

    mesh->buildNormalVectors();

    return mesh;
}
