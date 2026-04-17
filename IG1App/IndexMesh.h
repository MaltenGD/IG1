#pragma once
#include "Mesh.h"
#include <vector>
#include <numbers>
class IndexMesh : public Mesh
{
private:
	std::vector<GLuint> vIndexes;
	GLuint mIBO;
public:
	IndexMesh();
	void draw() const override;
	void load() override;
	void unload() override;
	void buildNormalVectors();
	
	static IndexMesh* generateByRevolution(const std::vector<glm::vec2>& profile,GLuint nSamples,GLfloat angleMax = 2 * std::numbers::pi);
};

