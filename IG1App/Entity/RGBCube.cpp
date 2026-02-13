#include "RGBCube.h"
using namespace glm;

RGBCube::RGBCube(GLdouble Lenght) : lenght(Lenght)
{
	mMesh = Mesh::generateRGBCubeTriangles(Lenght);

	//Se desplaza el cubo " - lenght " en el eje Z para prepararlo en la posición inicial del apartado opcional

	mModelMat = glm::translate(mModelMat, vec3(0, 0, -Lenght));
}

void RGBCube::update()
{
	rotation += 1;
	rotation = rotation % 360;

	//El bucle deberá generar una rotación en el cubo mediante la matriz de modelado
	//El bucle deberá generar una secuencia de rotaciónes, de forma que cuando el cubo alcance un cierto angulo, se cambie el eje de rotación

	//Primera secuencia, rotación sobre el eje X

	mModelMat = glm::rotate(glm::mat4(1.0f), glm::radians<float>(-rotation), glm::vec3(-lenght, 0, 0));
	/*mModelMat = glm::rotate(mModelMat, glm::radians<float>(1.0f), glm::vec3(1, 0, 0));*/ // TODO: preguntar si esta alternativa es mejor
}
