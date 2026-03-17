#include "Scene2.h"
#include "RegularPolygon.h"
#include "RGBTriangle.h"
#include "RGBRectangle.h"

void
Scene2::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	constexpr GLint TriangleRadius = 50;
	constexpr GLint TriangleX = 0;
	constexpr GLint TriangleY = 0;
	constexpr GLint SquareX = 0;
	constexpr GLint SquareY = 0;
	constexpr GLint CircleX = 0;
	constexpr GLint CircleY = 0;
	constexpr GLint squareSideLenth = 100;
	const GLfloat circleDiameter = squareSideLenth * glm::sqrt(2.0f);

	// Graphics objects (entities) of the scene
	opaque_gObjects.push_back(new RGBAxes(400.0));
	opaque_gObjects.push_back(new RGBTriangle(TriangleRadius, TriangleX, TriangleY, circleDiameter)); //Est?en la posición {R,0} siendo R el diámetro del
	opaque_gObjects.push_back(new RGBRectangle(squareSideLenth, squareSideLenth));
	opaque_gObjects.push_back(new RegularPolygon(60, circleDiameter, {1,0,1,1}));

}
