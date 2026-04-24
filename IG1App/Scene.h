#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Light.h"

#include <vector>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene();

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init() = 0; 

	virtual void update();
	void render(Camera const& cam) const;

	// load or unload scene data into the GPU
	void load();
	void uploadLights(Camera const& cam) const;
	void unload();
	virtual void rotate();
	virtual void orbit();

protected:
	void destroy();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> opaque_gObjects; // Entities (graphic objects) of the scene
	
	std::vector<Abs_Entity*> translucid_gObjects; // Entities (graphic objects) of the scene
	std::vector<Light*> gLights
};


#endif //_H_Scene_H_
