#include "RegularPolygon.h"


RegularPolygon::RegularPolygon(GLuint numVertex, GLdouble radius) : SingleColorEntity()
{
	mMesh = Mesh::generateRegularPolygon(numVertex, radius);
}
