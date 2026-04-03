#include "Shader.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>

using namespace glm;
#include <iostream>

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
}

void
Camera::setVM()
{
	mViewMat = lookAt(mEye, mLook, mUp); // glm::lookAt defines the view matrix
}

void
Camera::set2D()
{
	mEye = {0, 0, 500};
	mLook = {0, 0, 0};
	mUp = {0, 1, 0};
	mRadio = 100;
	mAng = -45.0f;
	setVM();
	setAxes();
}

void
Camera::set3D()
{
	mEye = {500, 500, 500};
	mLook = {0, 10, 0};
	mUp = {0, 1, 0};
	mRadio = 100;
	mAng = -45.0f;
	setVM();
	setAxes();
	//changePrj();
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
	// rotar u (X)
	// Up dand down	

	mFront = glm::rotate(glm::mat4(1.0f), glm::radians(cs), mRight) * glm::vec4(mFront, 0.0f);
	mLook = mEye + mFront;

	//xAngle += cs;
	//std::cout << xAngle << std::endl;
	//glm::vec3 direction = mLook - mEye;
	//std::cout << " " << direction.x <<  " " << direction.y << direction.z << " " << std::endl;
	//std::cout << mLook.y << std::endl;
	//mLook.y = mEye.y + direction.length() * glm::cos(glm::radians(xAngle));
	//mLook.z = mEye.z + direction.length() * glm::cos(glm::radians(xAngle));
	//std::cout << mLook.y << std::endl;
	//mLook += mUpward * cs;
	setVM();
}

void Camera::yawReal(GLfloat cs)
{
	// rotar v (Y)
	// derecha izquierda?????????
	mFront = glm::rotate(glm::mat4(1.0f), glm::radians(cs), mUpward) * glm::vec4(mFront, 0.0f);
	mLook = mEye + mFront;
	//mLook += mRight * cs;
	setVM();
}

void Camera::rollReal(GLfloat cs)
{
	//float angle = glm::dot(mRight, mUpward);
	//float value = glm::sin(glm::radians(angle - cs));
	//mUp = mUp + glm::vec3(value, value,value);
	//std::cout << glm::dot(mRight, mUpward) << std::endl;
	mUp = glm::rotate(glm::mat4(1.0f), glm::radians(cs), mFront) * glm::vec4(mUp, 0.0f);
	//mLook = mEye + mFront;
	setVM();
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
	else
	{
		mProjMat = frustum<float>(xLeft,
			xRight,
			yBot,
			yTop,
			mNearVal * mScaleFact,
			mFarVal * mScaleFact); //quizas esto al reves
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
	mRight = row(mViewMat,0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2);
}

void Camera::moveLR(GLfloat cs)
{
	mEye += mRight * cs;
	mLook += mRight * cs;
	setVM();
}

void Camera::moveFB(GLfloat cs)
{
	mEye += mFront* cs;
	mLook += mFront * cs;
	setVM();
}

void Camera::moveUD(GLfloat cs)
{
	mEye += mUpward* cs;
	mLook += mUpward* cs;
	setVM();
}

void Camera::changePrj()
{
	bOrto = !bOrto;
	int width = viewPort().width()/2;
	int height = viewPort().height()/2;
	if (bOrto)
	{
		mProjMat = ortho<float>(-width, width,
			-height, height,100, 10000);
	}
	else
	{
		mNearVal = 200;
		mFarVal = 10000;
		mProjMat = frustum<float>(-width, width, -height, height, mNearVal, mFarVal);
	}

}

void Camera::orbit(float incAng, float incY)
{
    mAng += incAng;
    mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
    mEye.z = mLook.z - sin(radians(mAng)) * mRadio;
    mEye.y += incY;
    setVM(); 
	setAxes();
}

void Camera::setCenital()
{
    mEye = glm::vec3{0,500,0};
    mLook = glm::vec3{0,0,0};
	mUp = { 0, 0, -1 };
	mRadio = 0;
	mAng = 0;
	setVM();
	setAxes();
}
