#include "SingleColorEntity.h"
class Star3D : public SingleColorEntity
{
public:
	Star3D(GLdouble radioExterior, GLuint numPuntas, GLdouble altura);
	void render(const glm::mat4& modelViewMat) const override;

private:

	glm::mat4 mModelMat180X;
};

