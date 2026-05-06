#include "Scene8.h"
#include "Entity/Sphere.h"
#include "Droid.h"
#include "Light.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

void Scene8::init()
{
	//// OpenGL basic setting
	//glClearColor(0, 0, 0, 1.0); // background color (alpha=1 -> opaque)
	//glEnable(GL_DEPTH_TEST);          // enable Depth test

	constexpr float SPHERE_RADIUS = 200.0f;
	constexpr float DROID_RADIUS = 20.0f;
	
	// Apartado 77
	constexpr float POSLIGHT_X = 0.0f;
	constexpr float POSLIGHT_Y = 280.0f;
	constexpr float POSLIGHT_Z = 0.0f;

	// 78
	constexpr float SPOTLIGHT_X = 0.0f;
	constexpr float SPOTLIGHT_Y = 0.0f;
	constexpr float SPOTLIGHT_Z = 300.0f;

	opaque_gObjects.push_back(new RGBAxes(400.0));

	droid = new Droid(DROID_RADIUS);
	glm::mat4 m = droid->modelMat();
	m = glm::translate<float>(m,glm::vec3(0, SPHERE_RADIUS + DROID_RADIUS,0));
	droid->setModelMat(m);

	node = new CompoundEntity();
	node->addEntity(droid);

	opaque_gObjects.push_back(node);
	

	// Apartado 77
	PosLight* posLight = new PosLight(0);
	posLight->setPosition(glm::vec3(POSLIGHT_X, POSLIGHT_Y, POSLIGHT_Z));
	posLight->setAmb(glm::vec3(0.25f, 0.25f, 0.25f));
	posLight->setDiff(glm::vec3(0.6f, 0.6f, 0.6f));
	posLight->setSpec(glm::vec3(0.0f, 0.2f, 0.0f));
	posLight->setEnabled(false);
	gLights.push_back(posLight);

	// SpotLight
	spotLight = new SpotLight(glm::vec3(SPOTLIGHT_X, SPOTLIGHT_Y, SPOTLIGHT_Z),1);
	spotLight->setAmb({ 0.25f, 0.25f, 0.25f });
	spotLight->setDiff({ 0.6f, 0.6f, 0.6f });
	spotLight->setSpec({ 0.0f, 0.2f, 0.0f });
	spotLight->setDirection(glm::vec3(0, 0, -1));
	spotLight->setCutoff(10, 30);
	spotLight->setEnabled(false);
	gLights.push_back(spotLight);

	droidLight = new SpotLight(glm::vec3(0, SPHERE_RADIUS + DROID_RADIUS, 0),2);
	droidLight->setAmb({ 0.25f, 0.25f, 0.25f });
	droidLight->setDiff({ 0.6f, 0.6f, 0.6f });
	droidLight->setSpec({ 0.0f, 0.2f, 0.0f });
	droidLight->setDirection(glm::vec3(0, -1, 0));
	droidLight->setCutoff(20, 50);
	droidLight->setEnabled(true);

	droid->setLight(droidLight);
	gLights.push_back(droidLight);

	Sphere* sphere = new Sphere(SPHERE_RADIUS, 30, 30);
	sphere->setColor(glm::vec4(171.0f / 255, 33.0f / 255, 72.0f / 255, 1));
	opaque_gObjects.push_back(sphere);
}


void Scene8::rotate() {
	glm::mat4 modelMat = node->modelMat();
	node->setModelMat(glm::rotate(modelMat, glm::radians<float>(2), glm::vec3(0, 1, 0)));
	//glm::vec4 lightPosition = droidLight->getPosition() * modelMat;
	//droidLight->setPosition(glm::vec3(lightPosition.x,lightPosition.y,lightPosition.z));
}

void Scene8::orbit() {
	glm::mat4 modelMat = node->modelMat();
	node->setModelMat(glm::rotate(modelMat, glm::radians<float>(2), glm::vec3(1, 0, 0)));

	//glm::vec4 lightPosition = droidLight->getPosition() * modelMat;
	//droidLight->setPosition(glm::vec3(lightPosition.x, lightPosition.y, lightPosition.z));
	droid->rotate();
}

void Scene8::handleInput(unsigned int key)
{
	//Scene::handleInput(key);
	switch (key)
	{
		case 'y':
			//std::cout << "pressing y" << std::endl;
			spotLight->setEnabled(!spotLight->enabled());
			//redisplay = true;
			break;
		case 'h':
			break;
		case 'T':
			if (droid && droid->getLight()) {
				bool newState = !droid->getLight()->enabled();
				droid->getLight()->setEnabled(newState);
			}
			break;
	}
}