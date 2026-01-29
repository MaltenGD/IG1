#include "RGBTriangle.h"

RGBTriangle::RGBTriangle(GLdouble radius, GLint Xpos, GLint Ypos ,GLfloat circleDiameter) : mSelfAngleDeg(0.0), circleDiameter(circleDiameter)
{
	mMesh = Mesh::createRGBTriangle(radius,Xpos, Ypos);
}

void RGBTriangle::update()
{

    mSelfAngleDeg += 5.0f;  // Grados por frame

    GLint triangleXpos = circleDiameter * glm::cos(glm::radians(mSelfAngleDeg));
    GLint triangleYpos = circleDiameter * glm::sin(glm::radians(mSelfAngleDeg));

    mModelMat = glm::mat4(1.0f);  // Se resetea la matriz identidad

    //Esto hace que el triángulo rote alrededor de la circunferencia
    mModelMat = glm::translate(mModelMat, glm::vec3(triangleXpos, triangleYpos, 0.0f));

    //Esto hace que rote sobre sí mismo (-angulo para que sea en sentido de las agujas del reloj)
    mModelMat = glm::rotate(mModelMat, glm::radians(-mSelfAngleDeg), glm::vec3(0, 0, 1.0));
}
