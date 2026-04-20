#include "Mesh.h"
#include <vector>
#include <numbers>
class IndexMesh : public Mesh
{
private:
	struct IndexedTriangle
	{
		int a;
		int b;
		int c;
	};
private:
	std::vector<GLuint> vIndexes;
	GLuint mIBO;
public:
	IndexMesh();
	void draw() const override;
	void load() override;
	void unload() override;
	void buildNormalVectors();
	
	static IndexMesh* generateByRevolution(const std::vector<glm::vec2>& profile,GLuint nSamples,GLfloat angleMax = 2 * std::numbers::pi, bool buildNormals = true);
	static IndexMesh* generateIndexedBox8(GLdouble l, bool buildNormals = true);
	static IndexMesh* generateIndexedBox(GLdouble l, bool buildNormals = true);

	static IndexMesh* generateSphere(GLdouble radius,GLuint nParallel, GLuint nMeridians);

private:
	void createTriangleWithIndex(std::vector<GLuint>& vIndexes, IndexedTriangle indexedTriangle);
};

