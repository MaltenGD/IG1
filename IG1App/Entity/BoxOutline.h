#pragma once
//#include "SingleColorEntity.h"
#include "EntityWithTexture.h"
#include "Texture.h"
class BoxOutline : public EntityWithTexture
{
private:
	Texture* _inside;
public:
	BoxOutline(GLfloat length, const char* outside_texture, const char* inside_texture);
	~BoxOutline();
	void render(const glm::mat4& modelViewMat) const override;

private:
	glm::vec3 mCoordinates{ 300, 10, -200 };
};

