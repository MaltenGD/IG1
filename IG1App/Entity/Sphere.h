#include "ColorMaterialEntity.h"

class Sphere : public ColorMaterialEntity
{
public:
	Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians);
	Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians,glm::vec3 colour);
};
