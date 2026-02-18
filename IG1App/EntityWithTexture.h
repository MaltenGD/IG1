#include "Entity.h"
#include "Texture.h"
#pragma once
class EntityWithTexture : public Abs_Entity
{
protected:

	Texture* mTexture = nullptr;
	bool mModulate = false;
public:

	EntityWithTexture(const char* shader = "texture", Texture* texture = nullptr);
	~EntityWithTexture() { delete mTexture; };

	virtual void render(const glm::mat4& modelViewMat) const override;

};

