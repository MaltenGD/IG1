#ifndef _H_Star3D_H_
#define _H_Star3D_H_

#include "EntityWithTexture.h"


class Star3D : public EntityWithTexture
{
public:
	Star3D(GLdouble radioExterior, GLuint numPuntas, GLdouble altura, const char* texture);
	void render(const glm::mat4& modelViewMat) const override;
	void update() override;

private:

	glm::mat4 mModelMat180X;
	GLfloat mAngle = 0.0f;
	glm::vec3 mCoordinates = { 150,20,-100 };
};

#endif // _H_Star3D_H_