#include "EntityWithTexture.h"
#include "Texture.h"

class Star3D : public EntityWithTexture
{
public:
	Star3D(GLdouble radioExterior, GLuint numPuntas, GLdouble altura, const char* texture);
	void render(const glm::mat4& modelViewMat) const override;
	void update() override;

private:

	glm::mat4 mModelMat180X;
	GLfloat mAngle = 0.0f;
	glm::vec3 mCoordinates = { 300,10,-200 };
};