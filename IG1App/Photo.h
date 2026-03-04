#include "EntityWithTexture.h"

class Photo : public EntityWithTexture
{
public:
    Photo(GLdouble width, GLdouble height, GLubyte alpha = 255);
    ~Photo() override;
    void update() override;

private:
	glm::vec3 mCoordinates{ 0, 10, 0 };
};
