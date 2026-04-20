#include "IndexMesh.h"
#include <algorithm>
#include <glm/gtc/constants.hpp>
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

IndexMesh* IndexMesh::generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, GLfloat angleMax, bool buildNormals)
{
	IndexMesh* mesh = new IndexMesh;

	mesh->mPrimitive = GL_TRIANGLES;
	int tamPerfil = profile.size();
	mesh->vVertices.reserve((nSamples + 1) * tamPerfil);
	mesh->vTexCoords.reserve((nSamples + 1) * tamPerfil);

	GLdouble theta1 = angleMax / nSamples;
	for (int i = 0; i <= nSamples; ++i) { // muestra i-ésima
		GLdouble c = cos(i * theta1), s = sin(i * theta1);
		for (int j = 0; j < tamPerfil; ++j) { // rota el perfil
			auto const& p = profile[j];
			mesh->vVertices.emplace_back(p.x * c, p.y, -p.x * s);
			mesh->vTexCoords.emplace_back(
				float(i) / nSamples,
				1.0f - float(j) / float(tamPerfil - 1)
			);
		}
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

	if (buildNormals) mesh->buildNormalVectors();

	return mesh;
}

IndexMesh* IndexMesh::generateIndexedBox8(GLdouble l, bool buildNormals)
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

	mesh->createTriangleWithIndex(mesh->vIndexes, {0, 2, 1});
	mesh->createTriangleWithIndex(mesh->vIndexes, {2, 3, 1});
	mesh->createTriangleWithIndex(mesh->vIndexes, {2, 4, 3});
	mesh->createTriangleWithIndex(mesh->vIndexes, {4, 5, 3});
	mesh->createTriangleWithIndex(mesh->vIndexes, {6, 7, 4});
	mesh->createTriangleWithIndex(mesh->vIndexes, {4, 7, 5});
	mesh->createTriangleWithIndex(mesh->vIndexes, {6, 0, 7});
	mesh->createTriangleWithIndex(mesh->vIndexes, {0, 1, 7});
	mesh->createTriangleWithIndex(mesh->vIndexes, {6, 4, 0});
	mesh->createTriangleWithIndex(mesh->vIndexes, {4, 2, 0});
	mesh->createTriangleWithIndex(mesh->vIndexes, {1, 3, 7});
	mesh->createTriangleWithIndex(mesh->vIndexes, {3, 5, 7});

	mesh->mNumVertices = mesh->vVertices.size();

	if (buildNormals) mesh->buildNormalVectors();

	return mesh;
}

IndexMesh* IndexMesh::generateIndexedBox(GLdouble l, bool buildNormals)
{
	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;

	mesh->vVertices.reserve(24);
	mesh->vIndexes.reserve(36);

	GLdouble len = l / GLdouble(2);

	mesh->vVertices.emplace_back(len, len, -len);   // 0
	mesh->vVertices.emplace_back(len, len, len);    // 1
	mesh->vVertices.emplace_back(len, -len, -len);  // 2
	mesh->vVertices.emplace_back(len, -len, len);   // 3
	mesh->vVertices.emplace_back(-len, len, -len);  // 4
	mesh->vVertices.emplace_back(-len, -len, -len); // 5
	mesh->vVertices.emplace_back(-len, len, len);   // 6
	mesh->vVertices.emplace_back(-len, -len, len);  // 7
	mesh->vVertices.emplace_back(-len, len, -len);  // 8
	mesh->vVertices.emplace_back(len, len, -len);   // 9
	mesh->vVertices.emplace_back(-len, len, len);   // 10
	mesh->vVertices.emplace_back(len, len, len);    // 11
	mesh->vVertices.emplace_back(-len, -len, -len); // 12
	mesh->vVertices.emplace_back(-len, -len, len);  // 13
	mesh->vVertices.emplace_back(len, -len, -len);  // 14
	mesh->vVertices.emplace_back(len, -len, len);   // 15
	mesh->vVertices.emplace_back(len, len, len);    // 16
	mesh->vVertices.emplace_back(-len, len, len);   // 17
	mesh->vVertices.emplace_back(len, -len, len);   // 18
	mesh->vVertices.emplace_back(-len, -len, len);  // 19
	mesh->vVertices.emplace_back(len, len, -len);   // 20
	mesh->vVertices.emplace_back(len, -len, -len);  // 21
	mesh->vVertices.emplace_back(-len, len, -len);  // 22
	mesh->vVertices.emplace_back(-len, -len, -len); // 23

	mesh->createTriangleWithIndex(mesh->vIndexes, {0, 1, 2});
	mesh->createTriangleWithIndex(mesh->vIndexes, {1, 3, 2});

	mesh->createTriangleWithIndex(mesh->vIndexes, {4, 5, 6});
	mesh->createTriangleWithIndex(mesh->vIndexes, {6, 5, 7});

	mesh->createTriangleWithIndex(mesh->vIndexes, {8, 10, 9});
	mesh->createTriangleWithIndex(mesh->vIndexes, {10, 11, 9});

	mesh->createTriangleWithIndex(mesh->vIndexes, {12, 14, 13});
	mesh->createTriangleWithIndex(mesh->vIndexes, {13, 14, 15});

	mesh->createTriangleWithIndex(mesh->vIndexes, {16, 17, 18});
	mesh->createTriangleWithIndex(mesh->vIndexes, {17, 19, 18});

	mesh->createTriangleWithIndex(mesh->vIndexes, {20, 21, 22});
	mesh->createTriangleWithIndex(mesh->vIndexes, {22, 21, 23});

	mesh->mNumVertices = mesh->vVertices.size();

	if (buildNormals) mesh->buildNormalVectors();

	return mesh;
}

IndexMesh* IndexMesh::generateSphere(GLdouble radius, GLuint nParallel, GLuint nMeridians)
{
	std::vector<glm::vec2> profile;
	profile.reserve(nParallel + 1);

	constexpr GLdouble PI = glm::pi<GLdouble>();
	const GLdouble rotationFactor = PI / nParallel;

	// Perfil de abajo a arriba: [-PI/2, +PI/2]
	for (GLuint i = 0; i <= nParallel; ++i)
	{
		GLdouble theta = -PI / 2 + i * rotationFactor;
		GLdouble x = radius * glm::cos(theta);
		GLdouble y = radius * glm::sin(theta);



		profile.emplace_back(x, y);
	}

	return IndexMesh::generateByRevolution(profile, nMeridians);
}

void IndexMesh::createTriangleWithIndex(std::vector<GLuint>& vIndexes, IndexedTriangle indexedTriangle)
{
	vIndexes.push_back(indexedTriangle.a);
	vIndexes.push_back(indexedTriangle.b);
	vIndexes.push_back(indexedTriangle.c);
}
