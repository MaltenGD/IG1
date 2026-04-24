#ifndef __Scene9_H__
#define __Scene9_H__

#include "Scene.h"

class CompoundEntity;

class Scene9 : public Scene
{
private:
	CompoundEntity* node = nullptr;

public:
	Scene9() = default;
	~Scene9() = default;

	void init() override;
};

#endif //__Scene9_H__
