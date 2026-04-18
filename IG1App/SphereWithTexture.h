#ifndef __SphereWithTexture_H__
#define __SphereWithTexture_H__

#include "EntityWithTexture.h"
#include "ColorMaterialEntity.h"
class SphereWithTexture : public EntityWithTexture
{
	private:

	protected:

	public:
		SphereWithTexture(GLdouble radius,GLuint nParallel, GLuint nMeridians, const char* texture);
};

#endif //__${safeitemname}_H__
