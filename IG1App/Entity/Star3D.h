#ifndef _H_Star3D_H_
#define _H_Star3D_H_

#include "EntityWithTexture.h"


class Star3D : public EntityWithTexture
{
public:
	Star3D(GLdouble radioExterior, GLuint numPuntas, GLdouble altura, const char* texture);
	void render(const glm::mat4& modelViewMat) const override;
	void update() override;
	void setPosition(const glm::vec3& position);

private:

	glm::mat4 mModelMat180X;
	GLfloat mAngle = 0.0f;
   glm::vec3 mCoordinates = { 0.0f, 0.0f, 0.0f };
};

#endif // _H_Star3D_H_