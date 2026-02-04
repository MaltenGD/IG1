#include "RGBCube.h"
using namespace glm;

RGBCube::RGBCube(GLdouble Lenght)
{
	mMesh = Mesh::generateRGBCubeTriangles(Lenght);
}