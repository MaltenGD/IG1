#ifndef __Droid_H__
#define __Droid_H__
#include "CompoundEntity.h"
#include "Light.h"
class SphereWithTexture;

class Droid : public CompoundEntity
{
private:
	SphereWithTexture* body;
	SpotLight* light;
public:
	//Droid();
	Droid(GLdouble radius);
	void setLight(SpotLight* droidLight) { light = droidLight; };
	~Droid();
	SpotLight* getLight() const { return light; };

	void rotate();
	void render(const glm::mat4& modelViewMat) const override;
};

#endif
