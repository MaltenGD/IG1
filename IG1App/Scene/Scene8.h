#ifndef __Scene8_H__
#define __Scene8_H__
#include "Scene.h"

class CompoundEntity;
class Droid;

class Scene8 : public Scene
{

private:
	CompoundEntity* node = nullptr;
	Droid* droid;
public:
	Scene8() = default;
	~Scene8() = default;

	void init() override;

	void orbit() override;
	void rotate() override;
};

#endif //__Scene8_H__
