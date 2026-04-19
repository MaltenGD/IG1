#ifndef __CompoundEntity_H__
#define __CompoundEntity_H__
#include "Entity.h"
#include <vector>
#include <utility>
class CompoundEntity : public Abs_Entity
{
	private:

	protected:
		std::vector<Abs_Entity*> gObjects;
	public:
		CompoundEntity() = default;
		~CompoundEntity();
		void addEntity(Abs_Entity* ae);

		template<typename... Entities>
		void addEntity(Entities&&... entities)
		{
			//(gObjects.push_back((std::forward<Entities>(entities)),...));
			(gObjects.push_back(std::forward<Entities>(entities)),...);
		}

		virtual void load() override;
		virtual void unload() override;
		void render(const glm::mat4& modelViewMat) const override;
};

#endif //__CompoundEntity_H__
