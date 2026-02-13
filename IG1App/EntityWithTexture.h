#include "Entity.h"
#include "Texture.h"
#pragma once
class EntityWithTexture : public Abs_Entity
{
protected:

	Texture* mTexture;
	bool mModulate;
public:

	EntityWithTexture(const char* shader);

	virtual void render(const glm::mat4& modelViewMat) const override;

};

