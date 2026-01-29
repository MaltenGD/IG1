#include "Cube.h"


Cube::Cube(GLdouble Lenght, glm::vec4 color) : SingleColorEntity(color)
{
	mMesh = Mesh::generateCube(Lenght);
}
