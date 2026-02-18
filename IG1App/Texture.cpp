#include "Texture.h"

#include "Image.h"

Texture::~Texture()
{
	if (mId != 0)
		glDeleteTextures(1, &mId);
}

void
Texture::init()
{
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);

	// Filters and clamping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // GL_CLAMP
}

void
Texture::bind()
{
	glActiveTexture(GL_TEXTURE0); // Para evitar el warning 
	//"[WARNING] Texture state usage warning: The texture object (0) bound to texture image unit 0 
	// does not have a defined base level and cannot be used for texture mapping."
	glBindTexture(GL_TEXTURE_2D, mId);
}

void
Texture::load(const std::string& name, GLubyte alpha)
{
	if (mId == 0)
		init();

	Image image;
	image.load(name);

	if (alpha != 255)
		image.setAlpha(alpha);

	mWidth = image.width();
	mHeight = image.height();

	GLint level = 0;  // Base image level
	GLint border = 0; // No border

	glBindTexture(GL_TEXTURE_2D, mId);
	glTexImage2D(GL_TEXTURE_2D,
	             level,
	             GL_RGBA,
	             mWidth,
	             mHeight,
	             border,
	             GL_RGBA,
	             GL_UNSIGNED_BYTE,
	             image.data());

	glBindTexture(GL_TEXTURE_2D, 0);
}

void
Texture::setWrap(GLuint wp) // GL_REPEAT, GL_CLAMP_TO_EDGE, ...
{
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wp);
	glBindTexture(GL_TEXTURE_2D, 0);
}
