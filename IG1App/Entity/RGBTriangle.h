#include "Entity.h"


class RGBTriangle :
    public EntityWithColors
{

private:
    GLfloat mSelfAngleDeg{0.0};
    GLfloat circleDiameter;


   public:
       RGBTriangle(GLdouble radius,GLint Xpos, GLint Ypos, GLfloat circleDiameter);
       void update() override;
};

