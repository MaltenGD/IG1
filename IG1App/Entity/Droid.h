#ifndef __Droid_H__
#define __Droid_H__
#include "CompoundEntity.h"
class Droid : public CompoundEntity
{
private: float view_angle = 0;
	public:
		Droid();
		Droid(GLdouble radius);
		~Droid();
};

#endif //__${safeitemname}_H__
