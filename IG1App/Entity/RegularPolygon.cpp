	#include "RegularPolygon.h"


	RegularPolygon::RegularPolygon(GLuint numVertex, GLdouble radius, glm::vec4 color) : SingleColorEntity(color)
	{
		// Se asume que este constructor (RegularPolygon::RegularPolygon)
		// debe operar tal y como los apartados de la escena 1, por lo tanto, el polígono debe ser hueco (isFilled = false)
		mMesh = Mesh::generateRegularPolygon(numVertex, radius);
	}
