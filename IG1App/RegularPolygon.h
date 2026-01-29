#include "SingleColorEntity.h"
class RegularPolygon :
    public SingleColorEntity
{

    public: 
        RegularPolygon(GLuint numVertex, GLdouble radius, glm::vec4 color);
};

