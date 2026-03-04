#include "Photo.h"
#include "IG1App.h"
Photo::Photo(GLdouble width, GLdouble height, GLubyte alpha) : EntityWithTexture(new Texture(), alpha)
{
    mMesh = Mesh::generateRectangleTextCor(width, height, 1, 1);
    mTexture->loadColorBuffer(IG1App::s_ig1app.viewPort().width(), IG1App::s_ig1app.viewPort().height());
    mModelMat = glm::translate<float>(glm::mat4(1.0f), glm::vec3(0, 10, 0)) * glm::rotate<float>(glm::mat4(1.0f), glm::pi<float>() / 2, glm::vec3(1, 0, 0));
    moveTo(mCoordinates);
}

Photo::~Photo() {
    delete mTexture;
    mTexture = nullptr;
}

void Photo::update()
{
    mTexture->loadColorBuffer(IG1App::s_ig1app.viewPort().width(), IG1App::s_ig1app.viewPort().height());
}