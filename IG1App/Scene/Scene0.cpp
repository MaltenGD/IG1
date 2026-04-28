#include "Scene0.h"
#include "Entity/Sphere.h"
#include "Material.h"

void
Scene0::init() // ESCENA VACÍA
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	opaque_gObjects.push_back(new RGBAxes(400.0));

	constexpr float PLANET_RADIUS = 60.0f;
	constexpr glm::vec3 LEFT_PLANET_POS = { 0.0f, 20.0f, 180.0f };
	constexpr glm::vec3 RIGHT_PLANET_POS = { 180.0f, 20.0f, 0.0f };

	// Planeta de color amarillo 
	Sphere* yellowPlanet = new Sphere(PLANET_RADIUS, 30, 30);
	yellowPlanet->setColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	yellowPlanet->moveTo(RIGHT_PLANET_POS);
	opaque_gObjects.push_back(yellowPlanet);

	// Planeta con material dorado
	Material goldMaterial;
	// Los valores de el material me los ha compartido mi gran amigo y gran ser hunmano Claudio, muy listo el Claudio.
	goldMaterial.setAmb({ 0.24f, 0.19f, 0.07f });
	goldMaterial.setDiff({ 0.75f, 0.60f, 0.22f });
	goldMaterial.setSpec({ 0.63f, 0.56f, 0.37f });
	goldMaterial.setExp(51.f);

	// Planeta dorado.
	Sphere* goldPlanet = new Sphere(PLANET_RADIUS, 30, 30);
	goldPlanet->setMaterial(goldMaterial);
	goldPlanet->moveTo(LEFT_PLANET_POS);
	opaque_gObjects.push_back(goldPlanet);

}