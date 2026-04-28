#ifndef __Scene8_H__
#define __Scene8_H__
#include "Scene.h"

class CompoundEntity;
class Droid;
class SpotLight;
class Scene8 : public Scene
{

private:
	CompoundEntity* node = nullptr;
	Droid* droid;
	SpotLight* spotLight;
	SpotLight* droidLight;
public:
	Scene8() = default;
	~Scene8() = default;

	void init() override;

	void orbit() override;
	void rotate() override;
	void handleInput(unsigned int key) override;
};

#endif //__Scene8_H__
