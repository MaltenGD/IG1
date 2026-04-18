#ifndef __CompoundEntity_H__
#define __CompoundEntity_H__
#include "Entity.h"
#include <vector>
class CompoundEntity : public Abs_Entity
{
	private:

	protected:
		std::vector<Abs_Entity*> gObjects;
	public:
		CompoundEntity() = default;
		~CompoundEntity();
		void addEntity(Abs_Entity* ae);

		virtual void load() override;
		virtual void unload() override;
		void render(const glm::mat4& modelViewMat) const override;
};

#endif //__CompoundEntity_H__
