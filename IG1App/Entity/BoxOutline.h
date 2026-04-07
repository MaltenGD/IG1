#ifndef BOX_OUTLINE_H
#define BOX_OUTLINE_H

#include "EntityWithTexture.h"

class Texture;

class BoxOutline : public EntityWithTexture
{
private:
	Texture* _inside = nullptr;
public:
	BoxOutline(GLfloat length, const char* outside_texture, const char* inside_texture);
	~BoxOutline();
	void render(const glm::mat4& modelViewMat) const override;
};

#endif // BOX_OUTLINE_H
