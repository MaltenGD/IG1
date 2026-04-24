#ifndef __Scene10_H__
#define __Scene10_H__

#include "Scene.h"

class CompoundEntity;

class Scene10 : public Scene
{
private:
	CompoundEntity* node = nullptr;

public:
	Scene10() = default;
	~Scene10() = default;

	void init() override;
};

#endif //__Scene10_H__
