#include "Entity.h"
class SingleColorEntity :
    public Abs_Entity
{
private: 
    glm::vec4 mColor;


public:
    SingleColorEntity(glm::vec4 color = {1,1,1,1});
    glm::vec4 getColor() const
    {
        return mColor;
    }
    void setColor( glm::vec4 const& newColor)
    {
        mColor = newColor;
    }

    void render(const glm::mat4& modelViewMat) const override;
};

