#ifndef __Scene8_H__
#define __Scene8_H__
#include "Scene.h"

class CompoundEntity;
class Scene8 : public Scene
{

private:
	CompoundEntity* Orbit_node = nullptr;
	CompoundEntity* Rotate_node = nullptr;
	
public:
	Scene8() = default;
	~Scene8() = default;

	void init() override;

	void orbit() override;
	void rotate() override;
};

#endif //__Scene8_H__
