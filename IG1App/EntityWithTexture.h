#include "Entity.h"
#include "Texture.h"
#pragma once
class EntityWithTexture : public Abs_Entity
{
protected:

	Texture* mTexture;
	bool mModulate;
public:

	EntityWithTexture(const char* texture,const char* shader = "texture");
	EntityWithTexture(Texture* texture,const char* shader = "texture");
	~EntityWithTexture();
	void setTexture(Texture* tex);
	virtual void render(const glm::mat4& modelViewMat) const override;

};

