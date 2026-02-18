#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>



class Mesh
{
public:
	static Mesh* generateRegularPolygon(GLuint numVertex, GLdouble radius, GLint Xpos = 0, GLint Ypos = 0);

	static Mesh* generateRectangle(GLdouble w, GLdouble h);

	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh

	static Mesh* createRGBTriangle(GLdouble radius, GLint Xpos, GLint Ypos);

	static Mesh* createRGBRectangle(GLdouble w, GLdouble h);

	static Mesh* generateCube(GLdouble length);

	static Mesh* generateRGBCubeTriangles(GLdouble length);

	static Mesh* generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw = 1, GLuint rh = 1);

	static Mesh* generateBoxOutline(GLdouble length);

	static Mesh* generateBoxOutlineTexCor(GLdouble length);

	static Mesh* generateStar3D(GLdouble re, GLuint np, GLdouble h);


	Mesh();
	virtual ~Mesh();

	Mesh(const Mesh& m) = delete;            // no copy constructor
	Mesh& operator=(const Mesh& m) = delete; // no copy assignment

	virtual void render() const;

	GLuint size() const { return mNumVertices; }; // number of elements
	std::vector<glm::vec3> const& vertices() const { return vVertices; };
	std::vector<glm::vec4> const& colors() const { return vColors; };

	void rotateDeg(GLdouble radius,GLint degrees);

	void load();
	void unload();

protected:
	GLuint mPrimitive =
		GL_TRIANGLES;          // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0; // number of elements ( = vVertices.size())
	std::vector<glm::vec3> vVertices; // vertex array
	std::vector<glm::vec4> vColors;   // color array
	std::vector<glm::vec2> vTexCoords; // vector de coordenadas
	// de textura

	virtual void draw() const;

	GLuint mVAO;  // vertex array object

private:
	GLuint mVBO;  // vertex buffer object
	GLuint mCBO;  // color buffer object
	GLuint mTCO; 
};

#endif //_H_Scene_H_
