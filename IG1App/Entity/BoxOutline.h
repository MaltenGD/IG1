#include "EntityWithTexture.h"
class BoxOutline : public EntityWithTexture
{
	public:
	BoxOutline(GLdouble Lenght, const char* shader, Texture* outsideTexure, Texture* insideTexture);
	~BoxOutline() { delete insideTex; };

	void render(const glm::mat4& modelViewMat) const override;

private:
	Texture* insideTex = nullptr;
};

