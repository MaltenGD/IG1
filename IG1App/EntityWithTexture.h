#ifndef ENTITY_WITH_TEXTURE_H
#define ENTITY_WITH_TEXTURE_H

#include "Entity.h"

class Texture;

class EntityWithTexture : public Abs_Entity
{
protected:

	Texture* mTexture = nullptr;
	bool mModulate = false;
public:

	EntityWithTexture(const char* texture);
	EntityWithTexture(const char* texture, GLubyte alpha);
	EntityWithTexture(Texture* texture, GLubyte alpha = 255);
	EntityWithTexture(GLubyte alpha = 255);
	~EntityWithTexture();
	void setTexture(Texture* tex);
	virtual void render(const glm::mat4& modelViewMat) const override;

};

#endif // ENTITY_WITH_TEXTURE_H

