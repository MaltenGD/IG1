#ifndef PHOTO_H
#define PHOTO_H

#include "EntityWithTexture.h"

class Photo : public EntityWithTexture
{
public:
    Photo(GLdouble width, GLdouble height, GLubyte alpha = 255);
    ~Photo() override;
    void update() override;
};

#endif // PHOTO_H