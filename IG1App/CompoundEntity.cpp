#include "CompoundEntity.h"
#include "Mesh.h"
CompoundEntity::~CompoundEntity()
{
    for (Abs_Entity* entity : gObjects)
    {
        delete entity;
        entity = nullptr;
    }
}

void CompoundEntity::addEntity(Abs_Entity* ae)
{
    gObjects.push_back(ae);
}

void CompoundEntity::load()
{
    for (Abs_Entity* entity : gObjects)
    {
        entity->load();
    }
}

void CompoundEntity::unload()
{
    for (Abs_Entity* entity : gObjects)
    {
        entity->unload();
    }
}

void CompoundEntity::render(const glm::mat4& modelViewMat) const
{
    if (!gObjects.empty())
    {
        glm::mat4 aMat = modelViewMat * mModelMat;
        for (Abs_Entity* entity : gObjects)
        {
            entity->render(aMat);
        }
    }
}
