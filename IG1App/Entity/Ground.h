#include "EntityWithTexture.h"

class Ground : public EntityWithTexture
{
public:
    Ground(GLdouble length, const char* shader, Texture* texture);
};

