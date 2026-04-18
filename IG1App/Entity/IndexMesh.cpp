#include "IndexMesh.h"
#include <algorithm>

using namespace std;
using namespace glm;

constexpr GLuint NONE = numeric_limits<GLuint>::max();

// Inicializar mIBO;
IndexMesh::IndexMesh()
{

}

void IndexMesh::draw() const
{
	glDrawElements(
		mPrimitive, // primitiva ( GL_TRIANGLES , etc.)
		vIndexes.size(), // n鷐ero de 韓dices
		GL_UNSIGNED_INT, // tipo de los 韓dices
		nullptr // offset en el VBO de 韓dices
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

		// Se suma la normal de la cara a las normales de los v閞tices que forman la cara
		vNormals[i0] += normal;
		vNormals[i1] += normal;
		vNormals[i2] += normal;
	}

	for (size_t i = 0; i < vNormals.size(); ++i)
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
	for (int i = 0; i <= nSamples; ++i) { // muestra i-ésima
		GLdouble c = cos(i * theta1), s = sin(i * theta1);
		for (auto p : profile) // rota el perfil
			mesh->vVertices.emplace_back(p.x * c, p.y, -p.x * s);
	}

	for (int i = 0; i < nSamples; ++i) // caras i a i + 1
		for (int j = 0; j < tamPerfil - 1; ++j) { // una cara
			if (profile[j].x != 0.0) // triángulo inferior
				for (auto [s, t] : { std::pair{i, j}, {i, j + 1}, {i + 1, j} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
			if (profile[j + 1].x != 0.0) // triángulo superior
				for (auto [s, t] : { std::pair{i, j + 1}, {i + 1, j + 1}, {i + 1, j} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
		}
	mesh->mNumVertices = mesh->vVertices.size();

	mesh->buildNormalVectors();

	return mesh;
}

IndexMesh* IndexMesh::generateIndexedBox8(GLdouble l)
{
	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;

	mesh->vVertices.reserve(8);
	mesh->vIndexes.reserve(36);

	GLdouble len = l / GLdouble(2);

	// Los 8 vertices
	mesh->vVertices.emplace_back(len, len, -len);
	mesh->vVertices.emplace_back(len, -len, -len);
	mesh->vVertices.emplace_back(len, len, len);
	mesh->vVertices.emplace_back(len, -len, len);
	mesh->vVertices.emplace_back(-len, len, len);
	mesh->vVertices.emplace_back(-len, -len, len);
	mesh->vVertices.emplace_back(-len, len, -len);
	mesh->vVertices.emplace_back(-len, -len, -len);

	//mesh->vIndexes.push_back();
	mesh->createTriangleWithIndex(mesh->vIndexes, {0, 1, 2});
	mesh->createTriangleWithIndex(mesh->vIndexes, {2, 1, 3});
	mesh->createTriangleWithIndex(mesh->vIndexes, {2, 3, 4});
	mesh->createTriangleWithIndex(mesh->vIndexes, {4, 3, 5});
	mesh->createTriangleWithIndex(mesh->vIndexes, {4, 5, 6});
	mesh->createTriangleWithIndex(mesh->vIndexes, {6, 5, 7});
	mesh->createTriangleWithIndex(mesh->vIndexes, {6, 7, 0});
	mesh->createTriangleWithIndex(mesh->vIndexes, {0, 7, 1});
	mesh->createTriangleWithIndex(mesh->vIndexes, {4, 6, 2});
	mesh->createTriangleWithIndex(mesh->vIndexes, {2, 6, 0});
	mesh->createTriangleWithIndex(mesh->vIndexes, {1, 7, 3});
	mesh->createTriangleWithIndex(mesh->vIndexes, {3, 7, 5});

	mesh->mNumVertices = mesh->vVertices.size();

	mesh->buildNormalVectors();

	return mesh;
}

void IndexMesh::createTriangleWithIndex(std::vector<GLuint>& vIndexes, IndexedTriangle indexedTriangle)
{
	vIndexes.push_back(indexedTriangle.a);
	vIndexes.push_back(indexedTriangle.b);
	vIndexes.push_back(indexedTriangle.c);
}
