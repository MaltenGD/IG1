#include "RegularPolygon.h"


RegularPolygon::RegularPolygon(GLuint numVertex, GLdouble radius, glm::vec4 color) : SingleColorEntity(color)
{
	mMesh = Mesh::generateRegularPolygon(numVertex, radius);
}
