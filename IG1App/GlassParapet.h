#ifndef GLASS_PARAPET_H
#define GLASS_PARAPET_H

#include "EntityWithTexture.h"

class Texture;


class GlassParapet : public EntityWithTexture
{
public:
	GlassParapet(GLdouble length,const char* texture, GLubyte alpha);
	~GlassParapet() override;
	//void render(const glm::mat4& modelViewMat) const override;
};

#endif // GLASS_PARAPET_H