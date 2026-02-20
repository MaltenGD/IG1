#include "Mesh.h"
#include <glm/gtc/constants.hpp>

using namespace std;
using namespace glm;

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = numeric_limits<GLuint>::max();

Mesh::Mesh()
	: mVAO(NONE)
	, mVBO(NONE)
	, mCBO(NONE)
{
}

Mesh::~Mesh()
{
	unload();
}

void
Mesh::draw() const
{
	glDrawArrays(
		mPrimitive,
		0,
		size()); // primitive graphic, first index and number of elements to be rendered
}

void Mesh::rotateDeg(GLdouble radius,GLint degrees)
{
	// rotation
}

void
Mesh::load()
{
	assert(mVBO == NONE); // not already loaded

	if (vVertices.size() > 0) { // transfer data
		glGenBuffers(1, &mVBO);
		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, vVertices.size() * sizeof(vec3), vVertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
		glEnableVertexAttribArray(0);

		//Para los colores
		if (vColors.size() > 0) {             // upload colors
			glGenBuffers(1, &mCBO);

			glBindBuffer(GL_ARRAY_BUFFER, mCBO);
			glBufferData(GL_ARRAY_BUFFER, vColors.size() * sizeof(vec4), vColors.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), nullptr);
			glEnableVertexAttribArray(1);
		}

		// Para las texturas
		if (vTexCoords.size() > 0)
		{
			glGenBuffers(1, &mTCO);
			glBindBuffer(GL_ARRAY_BUFFER, mTCO);
			glBufferData(GL_ARRAY_BUFFER,
				vTexCoords.size() * sizeof(vec2),
				vTexCoords.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
				sizeof(vec2), nullptr);
			glEnableVertexAttribArray(2);
		}
	}
}

void
Mesh::unload()
{
	if (mVAO != NONE) {
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		mVAO = NONE;
		mVBO = NONE;

		if (mCBO != NONE) {
			glDeleteBuffers(1, &mCBO);
			mCBO = NONE;
		}

		if (mTCO != NONE) glDeleteBuffers(1, &mTCO);
	}
}

void
Mesh::render() const
{
	assert(mVAO != NONE);

	glBindVertexArray(mVAO);
	draw();
}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* Mesh::generateRegularPolygon(GLuint numVertex, GLdouble radius, GLint Xpos, GLint Ypos)
{
	Mesh* ret = new Mesh();

	ret->mPrimitive = GL_LINE_LOOP;
	
	ret->mNumVertices = numVertex;

	ret->vVertices.reserve(numVertex);

	constexpr GLdouble PI = glm::pi<GLdouble>();

	const GLdouble rotationFactor = 2*PI / numVertex;

	GLdouble actualRotation = PI * 0.5; // Empieza en Pi medios (Pi/2)


	for (size_t i = 0; i < numVertex; ++i)
	{
		GLdouble X = radius * glm::cos(actualRotation);
		GLdouble Y = radius * glm::sin(actualRotation);

		ret->vVertices.emplace_back(X + Xpos, Y + Ypos, 0.0);

		actualRotation += rotationFactor;

	}

	return ret;


}

//Apartado 7
Mesh* Mesh::createRGBTriangle(GLdouble radius, GLint Xpos, GLint Ypos)
{
	Mesh* ret = Mesh::generateRegularPolygon(3, radius, Xpos, Ypos);
	//TODO: preguntar si es buena idea y/o necesario establecer un radio en el constructor.

	ret->mPrimitive = GL_TRIANGLES;

	ret->vColors.reserve(3);
	//Todo: Preguntar si m�s es eficiente guardar variables como ret->vColors en referencias "auto&" ejemplo: auto& vColors = ret->vColors;

	//ROJO
	ret->vColors.emplace_back(1, 0, 0, 1);

	//VERDE
	ret->vColors.emplace_back(0, 1, 0, 1);

	//AZUL
	ret->vColors.emplace_back(0, 0, 1, 1);

	return ret;
}
//Apartado 8
Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h)
{
	Mesh* ret = new Mesh();

	ret->mPrimitive = GL_TRIANGLE_STRIP;

	ret->mNumVertices = 4;

	ret->vVertices.reserve(ret->mNumVertices);

	ret->vVertices.emplace_back(-w, -h, 0);
	ret->vVertices.emplace_back(-w, h, 0);
	ret->vVertices.emplace_back(w, -h, 0);
	ret->vVertices.emplace_back(w, h, 0);

	return ret;
}

//Apartado 8
Mesh* Mesh::createRGBRectangle(GLdouble w, GLdouble h)
{
	Mesh* ret = Mesh::generateRectangle(w, h);

	ret->vColors.reserve(4);

	//ROJO (v�rtice 0: inferior izquierda)
	ret->vColors.emplace_back(1, 0, 0, 1);

	//VERDE (v�rtice 1: inferior derecha)
	ret->vColors.emplace_back(0, 1, 0, 1);

	//VERDE (v�rtice 2: superior izquierda)
	ret->vColors.emplace_back(0, 1, 0, 1);

	//AZUL (v�rtice 3: superior derecha)
	ret->vColors.emplace_back(0, 0, 1, 1);

	return ret;
}

Mesh* Mesh::generateCube(GLdouble length)
{
	Mesh* ret = new Mesh();

	ret->mPrimitive = GL_TRIANGLES;

	//TODO: preguntar si podemos crear metodos en mesh que modifiquen una mesh y le agreguen vertices, ejemplo: ret->addFace(lenght, angle, origin)
	ret->mNumVertices = 36;

	ret->vVertices.reserve(ret->mNumVertices);


	/// 1 . {0,0,0}
	/// 2 . {length,0,0}
	/// 3 . {length, 0 , length}
	/// 4 . {0,0, length}
	/// 5 . {length, length, length}
	/// 6 . {0, length, length}
	/// 7 . {0,length,0}
	/// 8 . {length, length, 0}

	


	// Tri�ngulos de Cara proyectada en Y y X . Estos triangulos deben ser visibles

	ret->vVertices.emplace_back(0, 0, length); // 4
	ret->vVertices.emplace_back(length, length, length); // 5
	ret->vVertices.emplace_back(0, length, length); // 6
	
	ret->vVertices.emplace_back(0, 0, length); // 4
	ret->vVertices.emplace_back(length, 0, length); // 3
	ret->vVertices.emplace_back(length, length, length); // 5

	// Tri�ngulos de Cara proyectada en Z y Y. Estos triangulos deben ser visibles


	ret->vVertices.emplace_back(length, 0, length); // 3
	ret->vVertices.emplace_back(length, 0, 0); // 2
	ret->vVertices.emplace_back(length, length, length); // 5

	ret->vVertices.emplace_back(length, length, length); // 5
	ret->vVertices.emplace_back(length, 0, 0); // 2
	ret->vVertices.emplace_back(length, length, 0); // 8


	// Tri�ngulo de Cara proyectada en Z y X . Estos triangulos deben ser visibles

	ret->vVertices.emplace_back(length, length, length); // 5
	ret->vVertices.emplace_back(0, length, 0); // 7
	ret->vVertices.emplace_back(0, length, length); // 6

	ret->vVertices.emplace_back(length, length, length); // 5
	ret->vVertices.emplace_back(length, length, 0); // 8
	ret->vVertices.emplace_back(0, length, 0); // 7

	//Triangulos de Cara inferior, tambien proyectados en Z y X (escondidos)

	ret->vVertices.emplace_back(0, 0, 0); // 1
	ret->vVertices.emplace_back(length, 0, 0); // 2
	ret->vVertices.emplace_back(length, 0, length); // 3

	ret->vVertices.emplace_back(0, 0, length); // 4
	ret->vVertices.emplace_back(0, 0, 0); // 1
	ret->vVertices.emplace_back(length, 0, length); // 3

	// Tri�ngulos de Cara proyectada en Z y Y. Estos triangulos deben estar escondidos

	ret->vVertices.emplace_back(0, 0, length); // 4
	ret->vVertices.emplace_back(0, length, length); // 6
	ret->vVertices.emplace_back(0, length, 0); // 7

	ret->vVertices.emplace_back(0, 0, length); // 4
	ret->vVertices.emplace_back(0, length, 0); // 7
	ret->vVertices.emplace_back(0, 0, 0); // 1

	// Tri�ngulos de Cara proyectada en Y y X . Estos triangulos deben estar escondidos

	ret->vVertices.emplace_back(0, 0, 0); // 1
	ret->vVertices.emplace_back(0, length, 0); // 7
	ret->vVertices.emplace_back(length, length, 0); // 8

	ret->vVertices.emplace_back(0, 0, 0); // 1
	ret->vVertices.emplace_back(length, length, 0); // 8
	ret->vVertices.emplace_back(length, 0, 0); // 2

	return ret;

	// Version de He con GL_TRIANGLE_STRIP
	//cube->vVertices.emplace_back(length, length, length); // 1
	//cube->vVertices.emplace_back(0, length, length);      // 2
	//cube->vVertices.emplace_back(length, 0, length);      // 3
	//cube->vVertices.emplace_back(0, 0, length);           // 4
	//cube->vVertices.emplace_back(0, 0, 0);                // 5
	//cube->vVertices.emplace_back(0, length, length);      // 6
	//cube->vVertices.emplace_back(0, length, 0);           // 7
	//cube->vVertices.emplace_back(length, length, 0);      // 8
	//cube->vVertices.emplace_back(0, 0, 0);                // 9
	//cube->vVertices.emplace_back(length, 0, 0);           // 10
	//cube->vVertices.emplace_back(length, 0, length);      // 11
	//cube->vVertices.emplace_back(length, length, 0);      // 12
	//cube->vVertices.emplace_back(length, length, length); // 13
	//cube->vVertices.emplace_back(0, length, length);      // 14
	//cube->vVertices.emplace_back(length, length, 0);      // 15
	//cube->vVertices.emplace_back(length, length, length); // 16
}

Mesh* Mesh::generateRGBCubeTriangles(GLdouble length)
{
	Mesh* ret = Mesh::generateCube(length);

	ret->vColors.reserve(36);

	// Tri�ngulos de Cara proyectada en Y y X . TRIANGULOS ROJOS

	ret->vColors.emplace_back(1, 0, 0, 1);
	ret->vColors.emplace_back(1, 0, 0, 1);
	ret->vColors.emplace_back(1, 0, 0, 1);

	ret->vColors.emplace_back(1, 0, 0, 1);
	ret->vColors.emplace_back(1, 0, 0, 1);
	ret->vColors.emplace_back(1, 0, 0, 1);
	

	// Tri�ngulos de Cara proyectada en Z y Y. TRIANGULOS VERDES


	ret->vColors.emplace_back(0, 1, 0, 1);
	ret->vColors.emplace_back(0, 1, 0, 1);
	ret->vColors.emplace_back(0, 1, 0, 1);

	ret->vColors.emplace_back(0, 1, 0, 1);
	ret->vColors.emplace_back(0, 1, 0, 1);
	ret->vColors.emplace_back(0, 1, 0, 1);


	// Tri�ngulo de Cara proyectada en Z y X . TRIANGULOS AZULES

	ret->vColors.emplace_back(0, 0, 1, 1);
	ret->vColors.emplace_back(0, 0, 1, 1);
	ret->vColors.emplace_back(0, 0, 1, 1);

	ret->vColors.emplace_back(0, 0, 1, 1);
	ret->vColors.emplace_back(0, 0, 1, 1);
	ret->vColors.emplace_back(0, 0, 1, 1);

	//Triangulos de Cara inferior, tambien proyectados en Z y X , TRIANGULOS AZULES

	ret->vColors.emplace_back(0, 0, 1, 1);
	ret->vColors.emplace_back(0, 0, 1, 1);
	ret->vColors.emplace_back(0, 0, 1, 1);

	ret->vColors.emplace_back(0, 0, 1, 1);
	ret->vColors.emplace_back(0, 0, 1, 1);
	ret->vColors.emplace_back(0, 0, 1, 1);

	// Tri�ngulos de Cara proyectada en Z y Y. Estos triangulos deben estar escondidos, TRIANGULOS VERDES

	ret->vColors.emplace_back(0, 1, 0, 1);
	ret->vColors.emplace_back(0, 1, 0, 1);
	ret->vColors.emplace_back(0, 1, 0, 1);

	ret->vColors.emplace_back(0, 1, 0, 1);
	ret->vColors.emplace_back(0, 1, 0, 1);
	ret->vColors.emplace_back(0, 1, 0, 1);

	// Tri�ngulos de Cara proyectada en Y y X . Estos triangulos deben estar escondidos, TRIANGULOS ROJOS

	ret->vColors.emplace_back(1, 0, 0, 1);
	ret->vColors.emplace_back(1, 0, 0, 1);
	ret->vColors.emplace_back(1, 0, 0, 1);

	ret->vColors.emplace_back(1, 0, 0, 1);
	ret->vColors.emplace_back(1, 0, 0, 1);
	ret->vColors.emplace_back(1, 0, 0, 1);

	return ret;


	// Version de He con GL_TRIANGLE_STRIP
	//cube->vColors.emplace_back(red);   // 1
	//cube->vColors.emplace_back(red);   // 2
	//cube->vColors.emplace_back(red);   // 3
	//cube->vColors.emplace_back(red);   // 4
	//cube->vColors.emplace_back(green); // 5
	//cube->vColors.emplace_back(blue);  // 6
	//cube->vColors.emplace_back(blue);  // 7
	//cube->vColors.emplace_back(blue);  // 8
	//cube->vColors.emplace_back(red);   // 9
	//cube->vColors.emplace_back(green); // 10
	//cube->vColors.emplace_back(green); // 11, sobreescribe
	//cube->vColors.emplace_back(green); // 12
	//cube->vColors.emplace_back(green); // 13
	//cube->vColors.emplace_back(blue);  // 14
	//cube->vColors.emplace_back(blue);  // 15
	//cube->vColors.emplace_back(blue);  // 16
	//cube->vColors.emplace_back(blue);  // 16
}

Mesh* Mesh::generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* ret = Mesh::generateRectangle(w, h);

	ret->vTexCoords.reserve(ret->mNumVertices);

	ret->vTexCoords.emplace_back(0, 0);
	ret->vTexCoords.emplace_back(0, rh);
	ret->vTexCoords.emplace_back(rw, 0);
	ret->vTexCoords.emplace_back(rw, rh);


	return ret;
}

Mesh* Mesh::generateBoxOutline(GLdouble length)
{
	Mesh* ret = new Mesh();

	ret->mPrimitive = GL_TRIANGLE_STRIP;

	ret->mNumVertices = 10;

	ret->vVertices.reserve(ret->mNumVertices);

	ret->vVertices.emplace_back(0, 0, 0); // 1 o 9
	ret->vVertices.emplace_back(0, length, 0); // 2 o 10
	ret->vVertices.emplace_back(length, 0, 0); // 3
	ret->vVertices.emplace_back(length, length, 0); // 4
	ret->vVertices.emplace_back(length, 0, length); // 5
	ret->vVertices.emplace_back(length, length, length); // 6
	ret->vVertices.emplace_back(0, 0, length); // 7
	ret->vVertices.emplace_back(0, length, length); // 8
	ret->vVertices.emplace_back(0, 0, 0); // 1 o 9
	ret->vVertices.emplace_back(0, length, 0); // 2 o 10

	return ret;


}

Mesh* Mesh::generateBoxOutlineTexCor(GLdouble length)
{
	Mesh* ret = Mesh::generateBoxOutline(length);

	ret->vTexCoords.reserve(ret->mNumVertices);

	ret->vTexCoords.emplace_back(0, 0); // vértice 1
	ret->vTexCoords.emplace_back(0, 1); // vértice 2
	ret->vTexCoords.emplace_back(1, 0); // vértice 3
	ret->vTexCoords.emplace_back(1, 1); // vértice 4
	ret->vTexCoords.emplace_back(2, 0); // vértice 5
	ret->vTexCoords.emplace_back(2, 1); // vértice 6
	ret->vTexCoords.emplace_back(3, 0); // vértice 7
	ret->vTexCoords.emplace_back(3, 1); // vértice 8
	ret->vTexCoords.emplace_back(4, 0); // vértice 9
	ret->vTexCoords.emplace_back(4, 1); // vértice 10

	return ret;
}

Mesh* Mesh::generateStar3D(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* ret = new Mesh();

	ret->mPrimitive = GL_TRIANGLE_FAN;
	ret->mNumVertices = (np * 2) + 2;
	ret->vVertices.reserve(ret->mNumVertices);

	float ri = re / 2;
	float x, y, xi, yi, angleIni = 0;
	constexpr GLdouble PI = glm::pi<GLdouble>();
	float angleToSum = 2* PI / float(ret->mNumVertices - 2);

	float angleIniInter = angleToSum;

	ret->vVertices.emplace_back(0, 0, 0);

	for (int i = 0; i < (ret->mNumVertices - 2) / 2; i++) {
		// circunferencia grande
		x = re * cos(angleIni);
		y = re * sin(angleIni);

		// circunferencia pequeña
		xi = ri * cos(angleIniInter);
		yi = ri * sin(angleIniInter);

		ret->vVertices.emplace_back(x, y, h);
		ret->vVertices.emplace_back(xi, yi, h);

		angleIni += angleToSum * 2;
		angleIniInter += angleToSum * 2;
	}

	x = re * cos(angleIni);
	y = re * sin(angleIni);
	ret->vVertices.emplace_back(x, y, h);

	return ret;

	//ret->mPrimitive = GL_TRIANGLE_FAN;

	//ret->vVertices.reserve((np * 2) + 2); // el origen de la estrella , np puntos exteriores, np puntos interiores y el ultimo para cerrar la estrella

		//ret->vVertices.emplace_back(0, 0, 0);

		//constexpr GLdouble PI = glm::pi<GLdouble>();

		//const GLdouble rotationFactor = PI / np;

		//GLdouble actualRotation = PI * 0.5; // Empieza en Pi medios (Pi/2)

		//size_t numPuntas = np;

		//float outerRadius = re;
		//float innerRadius = outerRadius / 2;

		//for (size_t i = 0; i < numPuntas; ++i)
		//{
		//	// Por cada bucle (por cada punta de la estrella) se dibuja un vertice exterior y uno interior

		//	// Primero el punto exterior
		//	GLdouble outerPointX = outerRadius * glm::cos(actualRotation);
		//	GLdouble outerPointY = outerRadius * glm::sin(actualRotation);

		//	ret->vVertices.emplace_back(outerPointX, outerPointY, h); // la altura (h) determina la posición del plano en el eje Z

		//	// Se actualiza la rotación para el punto interior
		//	actualRotation += rotationFactor;

		//	GLdouble innerPointX = innerRadius * glm::cos(actualRotation);
		//	GLdouble innerPointY = innerRadius * glm::sin(actualRotation);

		//	ret->vVertices.emplace_back(innerPointX, innerPointY, h);

		//	//Vuelvo a actualizar el angulo para el siguiente punto
		//	actualRotation += rotationFactor;

		//}

		//// Cierro la estrella con el mismo vertice con el que empezó.
		//ret->vVertices.emplace_back(ret->vVertices[1]);

		//return ret;

}



