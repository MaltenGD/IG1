#include "Photo.h"
#include "IG1App.h"
#include "Texture.h"

Photo::Photo(GLdouble width, GLdouble height, GLubyte alpha) : EntityWithTexture(new Texture(), alpha)
{
    mMesh = Mesh::generateRectangleTextCor(width, height, 1, 1);
    mTexture->loadColorBuffer(IG1App::s_ig1app.viewPort().width(), IG1App::s_ig1app.viewPort().height());
}

Photo::~Photo() {
    delete mTexture;
    mTexture = nullptr;
}

void Photo::update()
{
    mTexture->loadColorBuffer(IG1App::s_ig1app.viewPort().width(), IG1App::s_ig1app.viewPort().height());
}