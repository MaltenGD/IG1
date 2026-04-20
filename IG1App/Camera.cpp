#include "Shader.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>

using namespace glm;
#include <iostream>

constexpr float ASPECT_RATIO = 16.0 / 9.0;
constexpr float FOV = 60;

Camera::Camera(Viewport* vp)
	: mViewMat(1.0)
	, mProjMat(1.0)
	, xRight(vp->width() / 2.0)
	, xLeft(-xRight)
	, yTop(vp->height() / 2.0)
	, yBot(-yTop)
	, mViewPort(vp)
{
	setPM();
}

void
Camera::uploadVM() const
{
	Shader::setUniform4All("modelView", mViewMat);

	const glm::vec4 lightDirWorld = glm::vec4(glm::normalize(glm::vec3(-1.0f, -1.5f, -1.25f)), 0.0f); // invierto la luz (el toroide se veia rotado sobre la z 180deg)
	const glm::vec4 lightDirView = glm::vec4(glm::normalize(glm::vec3(mViewMat * lightDirWorld)), 0.0f);

	Shader::setUniform4All("lightDir", lightDirView);
}

void
Camera::setVM()
{
	mViewMat = lookAt(mEye, mLook, mUp); // glm::lookAt defines the view matrix
}

void
Camera::set2D()
{
	mEye = { 0, 0, 500 };
	mLook = { 0, 0, 0 };
	mUp = { 0, 1, 0 };
	mAng = 90.0f;
	mRadio = 500;
	setVM();
	setAxes();
}

void
Camera::set3D()
{
	mEye = { 500, 500, 500 };
	mLook = { 0, 10, 0 };
	mUp = { 0, 1, 0 };
	GLdouble dx = mEye.x - mLook.x;
	GLdouble dz = mEye.z - mLook.z;
	mRadio = sqrt(dx * dx + dz * dz);
	mAng = glm::degrees(atan2(-dz, dx));
	setVM();
	setAxes();
}

void
Camera::pitch(GLfloat a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::vec3(1.0, 0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
	setAxes();
}

void
Camera::yaw(GLfloat a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::vec3(0, 1.0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
	setAxes();
}

void
Camera::roll(GLfloat a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::vec3(0, 0, 1.0));
	// glm::rotate returns mViewMat * rotationMatrix
	setAxes();
}

void Camera::pitchReal(GLfloat cs)
{ 
	// No se modifica la posicion del la camara directamente, sino modificando el Up, el look y luego ya modificar 
	// El orden deberia ser:
	// 1. Cambiar la posicion del look o del Up para la rotacion
	// 2. Actualizar la matriz de vista con lookAt, ya que se ha cambiado de algunos de los componentes.
	// 3. Con el viewMat actualizado, actualizar de nuevo la posicion de la camara con setAxes.
	
	// Rota mLook alrededor del eje de mRight (sin cambiar mEye)
	mFront = glm::rotate(glm::mat4(1.0f), glm::radians(cs), mRight) * glm::vec4(mFront, 0.0f);
	mLook = mEye + mFront;
	setVM();
	setAxes();
}

void Camera::yawReal(GLfloat cs)
{
	// Rota mLook alrededor del eje de mUpg (sin cambiar mEye)
	mFront = glm::rotate(glm::mat4(1.0f), glm::radians(cs), mUpward) * glm::vec4(mFront, 0.0f);
	mLook = mEye + mFront;
	setVM();
	setAxes();
}

void Camera::rollReal(GLfloat cs)
{
	// Rota mUp alrededor del eje de mFront (sin cambiar mEye)
	mUp = glm::rotate(glm::mat4(1.0f), glm::radians(cs), mFront) * glm::vec4(mUp, 0.0f);
	setVM();
	setAxes();
}

void Camera::orbit(GLfloat incAng, GLfloat incY)
{
	mAng += incAng;
	mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(radians(mAng)) * mRadio;
	mEye.y += incY;
	std::cout << mEye.y << std::endl;
	setVM();
	setAxes();
}

void Camera::setCenital()
{
	mEye = { 0, 500, 0 };
	mLook = { 0, 0, 0 };
	mUp = { 0, 0, -1 };
	mAng = 0;
	mRadio = 0;
	setVM();
	setAxes();
}

void
Camera::setSize(GLdouble xw, GLdouble yh)
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}

void
Camera::setScale(GLdouble s)
{
	mScaleFact -= s;
	if (mScaleFact < 0)
		mScaleFact = 0.01;
	setPM();
}

void
Camera::setPM()
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = ortho(xLeft * mScaleFact,
			xRight * mScaleFact,
			yBot * mScaleFact,
			yTop * mScaleFact,
			mNearVal,
			mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
	else {
		float tan = glm::tan(glm::radians(FOV / 2));
		float top = mNearVal * tan;
		float bot = -top;
		float right = top * ASPECT_RATIO;
		float left = -right;

		mProjMat = frustum<float>(left * mScaleFact,
			right * mScaleFact,
			bot * mScaleFact,
			top * mScaleFact,
			mNearVal,
			mFarVal); //quizas esto al reves
	}
}

void
Camera::uploadPM() const
{
	Shader::setUniform4All("projection", mProjMat);
}

void
Camera::upload() const
{
	mViewPort->upload();
	uploadVM();
	uploadPM();
}

void Camera::setAxes()
{
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2); // Por que narices OpenGL mira a -Z

}

void Camera::moveLR(GLfloat cs)
{
	mEye += mRight * cs;
	mLook += mRight * cs;
	setVM();
}

void Camera::moveFB(GLfloat cs)
{
	mEye += mFront * cs;
	mLook += mFront * cs;
	setVM();
}

void Camera::moveUD(GLfloat cs)
{
	mEye += mUpward * cs;
	mLook += mUpward * cs;
	setVM();
}

void Camera::changePrj()
{
	bOrto = !bOrto;
	setPM();
}