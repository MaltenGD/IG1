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
	setVM();
	setAxes();
}

void
Camera::set3D()
{
	mEye = {500, 500, 500};
	mLook = {0, 10, 0};
	mUp = {0, 1, 0};
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
	mLook += mUpward * cs;
	setVM();
}

void Camera::yawReal(GLfloat cs)
{
	// rotar v (Y)
	// derecha izquierda?????????
	mLook += mRight * cs;
	setVM();
}

void Camera::rollReal(GLfloat cs)
{
	std::cout << glm::dot(mRight, mUpward) << std::endl;
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
		mNearVal = 500;
		mFarVal = 10000;
		mProjMat = frustum<float>(-width, width, -height, height, mNearVal, mFarVal);
	}

}
