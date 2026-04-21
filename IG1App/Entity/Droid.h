#ifndef __Droid_H__
#define __Droid_H__
#include "CompoundEntity.h"
class SphereWithTexture;
class Droid : public CompoundEntity
{
private:
	SphereWithTexture* body;

public:
	Droid();
	Droid(GLdouble radius);
	~Droid();

	void rotate();
};

#endif
